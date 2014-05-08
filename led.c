/* led.c
 * Updates LED status to reflect lock states
 * May eventually allow for LEDs to indicate other information
 * Utilises hardware PWM features
 */

 
 #include "led.h"
 #include <avr/io.h>
 
 
 void led_init( )
 {
	//Enable PWM on these pins see 32u4 datasheet p. 167 for more details
	TCCR4B = 0b10000001; // PWM Invert, No clock division, enable timer.
	TCCR4C = 0b00000101; // Toggle on compare, fast PWM enable
	OCR4D = 0xF0; //Set PWM duty cycle
	
	//DDRD controls if LED is on (with PWM) or off.
	DDRD |= (1<<LED1) | (1<<LED2); //Both LEDs on
	
	//Debug: Set outputs
	//PORTD |= 1<<LED1) | (1<<LED2);
	//PORTD doesnt seem to actually do anything in this case, even though it should
	
 }
 
 //Updates LEDs based on passed in parameters
 void update_leds(uint8_t status)
 {
	//Check to see if caps lock led should be on
	if(status & (1<<CAPS_LOCK))
	{
		//Enable
		DDRD |= (1<<LED1);
	}
	else
	{
		//Disable
		DDRD &= ~(1<<LED1);
	}
	//Check to see if scroll lock led should be on
	if(status & (1<<SCROLL_LOCK))
	{
		//Enable
		DDRD |= (1<<LED2);
	}
	else
	{
		//Disable
		DDRD &= ~(1<<LED2);
	}
 }