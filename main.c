/* main.c
 * The entry point for the keyboard firmware.
 * Initializes interfaces, and loops through keyboard functions
 * 
 */

//I can't remember which of these includes are no longer needed in this file.
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usb_keyboard_debug.h"
#include "keyboard.h"
#include "bluefruit.h"
#include "print.h"
#include "uart.h"
#include "matrix.h"
#include "led.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n)) //Simple macro to set clock prescaler
 int main(void);
 int main( )
 {
	// set for 8 MHz clock
	CPU_PRESCALE(1);
	//Initialize keyboard
	keyboard_init();
	//Main while loop
	while(1)
	{
		keyboard_main();
		bluefruit_check_uart();
	}
		
	return 0;
}