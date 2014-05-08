#ifndef matrix_h__
#define matrix_h__

void matrix_init(void);
void matrix_scan(void);
void matrix_print(void);

#define NUMROWS 6			// Number of Rows
#define NUMCOLS 16			// Number of Columns
#define NUMKEYS 96			// Number of posible keys in matrix
#define COLMASK 0b00001111  // PORTB Columns Mask
#define ROWMASK 0b01110000	// PORTB Rows Mask
#define ROWSHIFT 4			// PORTB number of shifts to get rows
#define B7 7				// B7
#define DDRB_INI 0b01111111 // All output, except for B7

// MSB represents Mux output, bits 4-6 represent mux select lines (rows)
//  and bits 0-3 represent the decoder select lines (columns)
#define CHECK_B 0b01100000  

#endif