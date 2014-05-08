/* Keyboard.c
 * Detects changes in matrix, translates those changes
 * into keycodes, and generates keyboard reports.
 * 
 */
 
 #include "keyboard.h"
 #include "matrix.h"
 #include "layout.h"
 #include "usb_keyboard_debug.h"
 #include "print.h"
 #include "bluefruit.h"
 #include "led.h"
 #include <util/delay.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>

extern uint16_t matrix_rows[NUMROWS]; //defined in matrix.c
extern uint16_t matrix_last[NUMROWS]; //defined in matrix.c
extern volatile uint8_t keyboard_leds; //defined in usb_keyboard_debug.c
static keyboard_report key_report={0,{0,0,0,0,0,0}};

//Keyboard initialization function
void keyboard_init( )
{
	//Initialize Matrix,USB,Bluefruit,LEDs
	matrix_init();
	usb_init();
	bluefruit_init();
	led_init();
	//Set keyboard report for both protocols
	usb_keyboard_set_report(&key_report); //For usb
	bluefruit_keyboard_set_report(&key_report);//For Bluetooth
	//Decide which Protocol to use based on current USB state
	_delay_ms(50); // a 50ms wait to ensure systems are ready
	// Initial check to determine USB connection state
	//  Also determine which interface to use
	if(USBSTA & (1<<VBUS))
	{
		//Disable bluetooth enable USB
		usb_init(); // Enable USB
		bluefruit_disable( ); //Disable bluefruit
	}
	else
	{
		//Disable USB enable bluetooth
		usb_disable();
		bluefruit_init(); //enable bluefruit
	}
}
 //Keyboard main function
 //Handles all keyboard related tasks
 void keyboard_main( )
 {
	//Update LEDs if USB in use (bluetooth uses different method)
	if(!bluefruit_configured())
		update_leds(keyboard_leds);
	
	uint8_t needs_debounce = 0; // For determining if matrix needs debouncing
	uint16_t matrix_changed = 0;
	matrix_scan();
	// Now that we have scanned the matrix, determine if any actions need to be done
	for (uint8_t row = 0; row < NUMROWS; row++)
	{
		//Check to see if switches in this row has changed
		if ((matrix_changed = matrix_rows[row] ^ matrix_last[row]))
		{
			//At least one switch has changed in this row
			needs_debounce = 1; //We need to debounce
			for (int col = 0; col < NUMCOLS; col++)
			{
				//Find out which columns have changed and act
				if(matrix_changed & ((uint16_t)1<< col))
				{
					//This switch has changed, do whatever the switch was programmed to do
					if(matrix_rows[row] & ((uint16_t)1<< col))
					{
						//Keydown event
						key_execute(get_keycode(row,col),KEY_IS_DOWN);
						//phex(get_keycode(row,col).type);
						//print(":");
						//phex(get_keycode(row,col).code);
						//print(" key is down\n");
					}
					else
					{
						//Keyup event
						key_execute(get_keycode(row,col),KEY_IS_UP);
						//phex(get_keycode(row,col).type);
						//print(":");
						//phex(get_keycode(row,col).code);
						//print(" key is up\n");
					}
					
				}
			}
			matrix_last[row] = matrix_rows[row]; //Row has been dealt with
		}
		else
		{
			//Nothing has changed, do nothing?
		}
	}
	//Allow switch state to stabilize if an edge is detected.
	if (needs_debounce)
		_delay_us(DEBOUNCE_TIME);
 }
 
 //Key Execute function
 //Decodes a keycode, and executes depending on codetype
 void key_execute(keycode aKey, uint8_t down)
 {
	print("inside key_execute\n");
	phex(aKey.type);
	print("<-Type:Code->");
	phex(aKey.code);
	print("\n");
	switch(aKey.type)
	{
		case TYPE_KEY:
			//Check for type, and call functions
			if(down)
				add_key(aKey.code);
			else
				del_key(aKey.code);
		break;
		case TYPE_MOD:
			//Check for type, and call functions
			if(down)
				add_mod(aKey.code);
			else
				del_mod(aKey.code);
		break;
		case TYPE_MEDIA:
		case TYPE_MOUSE:
			//Placeholder if mouse and media keys implemented
		break;
		case TYPE_MOMENTARY:
			//For mementary layer changes
			clear_keyboard(); //Clear all current plessed keys, because they may not exist in new layer
			if(down)
				set_current_layer(aKey.code);
			else
				set_current_layer(0); //Return to default layer
		break;
		case TYPE_TOGGLE:
			//For toggleing layer changes
			if(down && (aKey.code ^ get_current_layer()) )
			{
				clear_keyboard();
				set_current_layer(aKey.code);
			}
		break;
		case TYPE_MISC:
			//Miscelaneous functions need special treatment
			switch(aKey.code)
			{
				case CODE_JMP_BOOT:
					//Jump to boot loader
					if(down) //Only want to activate on key-down
					{
						jump_bootloader();
					}
					break;
				case CODE_BR_UP:
					//Raise brightness of LEDS
					//In steps of 24
					if(down) //Only want to activate on key-down
					{
						if(OCR4D < 0xF0) OCR4D += 0x20;
					}
					break;
				case CODE_BR_DOWN:
					//Lower brightness of LEDS
					//In steps of 24
					if(down) //Only want to activate on key-down
					{
						if(OCR4D > 0x10) OCR4D -= 0x20;
					}
					break;
			}
			break;
		default:
			//Default case: Unknown Keytype
			//Print error and do nothing
			print("Unknown Key Type: ");
			phex(aKey.type);
			pchar('\n');
	}
 }
 
 //Adds a key to keyboard's report and then sends
 void add_key(uint8_t aKey)
 {
	//Add a key to report and send
	for(uint8_t i = 0; i < KEYS_PER_REPORT; i++)
	{
		//Check for empty spot in report if available, otherwise do nothing
		if(key_report.keys[i] == 0)
		{
			key_report.keys[i] = aKey;
			//send report
			keyboard_send_report();
			break;
		}
	}
 }
 
 //Deletes a key from keyboard's report and then sends
 void del_key(uint8_t aKey)
 {
	//delete a key from report and send
	for(uint8_t i = 0; i < KEYS_PER_REPORT; i++)
	{
		//Check for matching key in report, and delete if present
		if(key_report.keys[i] == aKey)
		{
			key_report.keys[i] = 0;
			//send report
			keyboard_send_report();
			break;
		}
	}
 }
 
 //Adds a mod to keyboard report and then sends
 void add_mod(uint8_t aMod)
 {
	//Or the mod into mods
	key_report.mods |= aMod;
	//Send report
	keyboard_send_report();
 }
 
 //Deletes a mod from keyboard report and then sends
 void del_mod(uint8_t aMod)
 {
	//And the mod out of mods
	key_report.mods &= ~aMod;
	//Send Report
	keyboard_send_report();
 }
 
 //Clears and then sends the current keyboard report
 void clear_keyboard( )
 {
	//Clear out keyboard report
	key_report.mods = 0;
	for (uint8_t i = 0; i < KEYS_PER_REPORT; i++)
		key_report.keys[i] = 0;
	//Send report
	keyboard_send_report();
 }
 
 //Sends a keyboard report depending on active protocol
 void keyboard_send_report( )
 {
	//Debug toggle bluetooth status
	//Check to see if USB active
	if(bluefruit_configured())
	{
		//Send keyboard report using Bluetooth
		bluefruit_keyboard_send();
		print("Sent Bluetooth Report!\n");
	}
	else
	{
		//Send keyboard report using USB
		usb_keyboard_send();
		//bluefruit_keyboard_send(); //debug also send bluetooth report
		print("Sent USB Report!\n");
	}
 }
 
 //Jump to bootloader
 //courtest of PJRC <http://www.pjrc.com/teensy/jump_to_bootloader.html>
 void jump_bootloader( )
 {
	cli();
	// disable watchdog, if enabled
	// disable all peripherals
	UDCON = 1;
	USBCON = (1<<FRZCLK);  // disable USB
	UCSR1B = 0;
	_delay_ms(5);
	#if defined(__AVR_AT90USB162__)                // Teensy 1.0
		EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0;
		TIMSK0 = 0; TIMSK1 = 0; UCSR1B = 0;
		DDRB = 0; DDRC = 0; DDRD = 0;
		PORTB = 0; PORTC = 0; PORTD = 0;
		asm volatile("jmp 0x3E00");
	#elif defined(__AVR_ATmega32U4__)              // Teensy 2.0
		EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
		TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
		DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
		PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
		asm volatile("jmp 0x7E00");
	#elif defined(__AVR_AT90USB646__)              // Teensy++ 1.0
		EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
		TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
		DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
		PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
		asm volatile("jmp 0xFC00");
	#elif defined(__AVR_AT90USB1286__)             // Teensy++ 2.0
		EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
		TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
		DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
		PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
		asm volatile("jmp 0x1FC00");
	#endif
}