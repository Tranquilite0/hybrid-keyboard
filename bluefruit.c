/* Bluefruit comminucation library
 * Handles all bluefruit communication functions
 * 
 *
 */

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "bluefruit.h"
#include "uart.h"
#include "print.h"
#include "led.h"

//Keyboard report pointer
static keyboard_report *key_report = NULL;

//Bluefruit initialiazation
//Not sure about all that is required so far
//Currently just a wrapper for serial initialization
void bluefruit_init( )
{
	//Configure needed IO pins
	BF_RESET_CONFIG;
	BF_PAIR_CONFIG;
	//Initialize uart
	uart_init(9600);
	//Disable Reset pin
	BF_RESET_OFF;
	BF_PAIR_OFF; //Make sure pair button is not pressed
}

//Bluefruit disable
//Saves power and prevents accidental bluetooth communication
void bluefruit_disable( )
{
	//Enable Reset pin
	BF_RESET_ON;
	// Anything else that needs to be done?
}

//For determining if bluefruit is configured
uint8_t bluefruit_configured( )
{
	return BF_RESET_READ;
}

void bluefruit_keyboard_set_report(keyboard_report *to_set)
{
	key_report = to_set;
}

//Sends a keyboard report over serial to bluefruit
int8_t bluefruit_keyboard_send( )
{
	//Check to see if bluefruit has been configured
	if(!bluefruit_configured( ) || key_report == NULL)
		return -1;
	//Let bluefruit know we are sending a raw keyboard report
	uart_putchar(0xFD);
	//Send mods
	uart_putchar(key_report->mods);
	//Need to send empty byte between mods and keys
	uart_putchar(0x00);
	//Now send keys in report
	for(uint8_t i = 0; i < KEYS_PER_REPORT; i++)
	{
		uart_putchar(key_report->keys[i]);
	}
	
	return 0;
}

//Check and parse revieved messages over UART
void bluefruit_check_uart( )
{
	// Check for information over UART interface
	uint8_t numInBuf = uart_available();
	if(numInBuf > 0)
	{
		for(int i = 0; i < numInBuf; i++)
		{
			uint8_t aChar = uart_getchar();
			if(aChar == 'N')
			{
				//See if next char in sequence is what we want
				aChar = uart_getchar();
				if(aChar == 'L')
				{
					//We have a match, read led statuses
					uint8_t led_status = 0;
					//Consume the ':'
					uart_getchar();
					//Get numlock status
					if (uart_getchar() == 'Y')
						led_status |= (1<<NUM_LOCK);
					//Consume " CL:"
					uart_getchar();
					uart_getchar();
					uart_getchar();
					uart_getchar();
					if (uart_getchar() == 'Y')
						led_status |= (1<<CAPS_LOCK);
					//Consume " SL:"
					uart_getchar();
					uart_getchar();
					uart_getchar();
					uart_getchar();
					if (uart_getchar() == 'Y')
						led_status |= (1<<SCROLL_LOCK);
					//Now update LED status
					update_leds(led_status);
					//Now output led status in binary form
					print("LED status -> ");
					pbin(led_status);
					//put newline in aChar
					aChar = uart_getchar();
					//Make sure that for loop is exited
					i = numInBuf;
				}
				else
				{
					//This is not the sequence you are looking for
					//Print out eaten char
					pchar('N');
					
				}
			}
			pchar(aChar);
		}
	}
}