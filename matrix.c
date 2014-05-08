/* Matrix.c
 * Handles all physical matrix related functions
 * Checks and stores status of all keyswitches
 *
 */
 
#include "matrix.h"
#include "print.h"
#include <avr/io.h>
#include <util/delay.h>

uint16_t matrix_rows[NUMROWS]; // Contains all keyswitch information
uint16_t matrix_last[NUMROWS]; // Last matrix that was scanned

// Matrix initialization function
// Sets registers
void matrix_init( )
{
	DDRB = DDRB_INI; //Initialise DDRB register
	PORTB = 0; //set outputs to 0
	for (int i = 0; i < NUMROWS; i++)
	{
		//Initialize Matrix switch state
		matrix_rows[i] = matrix_last[i] = 0;
	}
}

// Matrix Scan function
// Checks status of all keyswitches and stores results in matrix_rows
void matrix_scan( )
{
	//Current matrix state becomes previous matrix state
	for(uint8_t i = 0; i < NUMROWS; i++)
		matrix_rows[i] = matrix_last[i];
	
	//Systematically check all switches
	for(PORTB = 0; (PORTB < CHECK_B); PORTB++)
	{
		//Check Mux output status
		if (PINB & (1 << B7))
		{
			//Switch is on
			matrix_rows[PORTB >> ROWSHIFT] |= ((uint16_t)1 << (PORTB & COLMASK));
		}
		else
		{
			//Switch is off
			matrix_rows[PORTB >> ROWSHIFT] &= ~((uint16_t)1 << (PORTB & COLMASK));
		}
	}
}

//Matrix Print function
//Prints the status of the keyswitch matrix to debug console
void matrix_print( )
{
	for(uint8_t i = 0; i < NUMROWS; i++)
	{
		pbin16r(matrix_rows[i]);
		print("\n");
	}
	print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}