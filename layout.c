/* layout.c
 * Used for translating pressed keyswitches into
 * keycodes that are then sent by USB or Bluetooth
 * 
 */

#include "layout.h"
#include <avr/pgmspace.h>
#include "matrix.h"
#include "print.h"

//For determining current layer
static uint8_t current_layer = 0;

//Create Keycode Layout, store in PROGMEM
const uint16_t layout[][NUMKEYS] PROGMEM = { 
	{ //Layer 0
//      | Col 0  |  Col 1  |  Col 2  |  Col 3  |  Col 4  |  Col 5  |  Col 6  |  Col 7  |  Col 8  |  Col 9  |  Col 10 |  Col 11 |  Col 12 |  Col 13 |  Col 14 |  Col 15 |
/*Row 0*/KB_ESC  , KB_NONE , KB_F1   , KB_F2   , KB_F3   , KB_F4   , KB_F5   , KB_F6   , KB_F7   , KB_F8   , KB_F9   , KB_F10  , KB_F11  , KB_F12  , KB_PSCRN, KB_SCRLK, 
/*Row 1*/KB_TILDE, KB_1    , KB_2    , KB_3    , KB_4    , KB_5    , KB_6    , KB_7    , KB_8    , KB_9    , KB_0    , KB_MINUS, KB_EQUAL, KB_BKSPC, KB_INS  , KB_HOME , 
/*Row 2*/KB_TAB  , KB_Q    , KB_W    , KB_E    , KB_R    , KB_T    , KB_Y    , KB_U    , KB_I    , KB_O    , KB_P    , KB_LBRCE, KB_RBRCE, KB_BSLSH, KB_DEL  , KB_END  , 
/*Row 3*/KB_CAPLK, KB_A    , KB_S    , KB_D    , KB_F    , KB_G    , KB_H    , KB_J    , KB_K    , KB_L    , KB_SMCLN, KB_QUOTE, KB_NONE , KB_ENTER, KB_PGUP , KB_PAUSE, 
/*Row 4*/KB_LSHFT, KB_Z    , KB_X    , KB_C    , KB_V    , KB_B    , KB_N    , KB_M    , KB_COMMA, KB_DOT  , KB_SLASH, KB_NONE , KB_RSHFT, KB_NONE , KB_PGDN , KB_UP   , 
/*Row 5*/KB_LCTRL, KB_LGUI , KB_LALT , KB_NONE , KB_NONE , KB_SPACE, KB_NONE , KB_NONE , KB_NONE , KB_RALT , KB_RGUI , MLAYER_1, KB_RCTRL, KB_LEFT , KB_DOWN , KB_RIGHT 
	},
	{ //Layer 1
//      | Col 0  |  Col 1  |  Col 2  |  Col 3  |  Col 4  |  Col 5  |  Col 6  |  Col 7  |  Col 8  |  Col 9  |  Col 10 |  Col 11 |  Col 12 |  Col 13 |  Col 14 |  Col 15 |
/*Row 0*/KB_ESC  , KB_NONE , KB_F1   , KB_F2   , KB_F3   , KB_F4   , KB_F5   , KB_F6   , KB_F7   , KB_F8   , KB_F9   , KB_F10  , KB_F11  , KB_F12  , KB_PSCRN, KB_SCRLK, 
/*Row 1*/KB_TILDE, KB_1    , KB_2    , KB_3    , KB_4    , KB_5    , KB_6    , KB_7    , KB_8    , KB_9    , KB_0    , KB_MINUS, KB_EQUAL, KB_BKSPC, KB_INS  , KB_HOME , 
/*Row 2*/KB_TAB  , KB_Q    , KB_W    , KB_E    , KB_R    , KB_T    , KB_Y    , KB_U    , KB_I    , KB_O    , KB_P    , KB_LBRCE, KB_RBRCE, KB_BSLSH, KB_DEL  , KB_END  , 
/*Row 3*/KB_CAPLK, KB_A    , KB_S    , KB_D    , KB_F    , KB_G    , KB_H    , KB_J    , KB_K    , KB_L    , KB_SMCLN, KB_QUOTE, KB_NONE , KB_ENTER, KB_PGUP , JMP_BOOT, 
/*Row 4*/KB_LSHFT, KB_Z    , KB_X    , KB_C    , KB_V    , KB_B    , KB_N    , KB_M    , KB_COMMA, KB_DOT  , KB_SLASH, KB_NONE , KB_RSHFT, KB_NONE , KB_PGDN , BR_UP   , 
/*Row 5*/KB_LCTRL, KB_LGUI , KB_LALT , KB_NONE , KB_NONE , KB_SPACE, KB_NONE , KB_NONE , KB_NONE , KB_RALT , KB_RGUI , MLAYER_1, KB_RCTRL, KB_LEFT , BR_DOWN , KB_RIGHT 
	} 	
};

//Allows you to change the current layer
void set_current_layer(uint8_t in_layer)
{
	current_layer = in_layer;
}

uint8_t get_current_layer( )
{
	return current_layer;
}

//Get keycode function
//Use row and column to get keycode out of array
//Then cast to keycode struct and return
keycode get_keycode(uint8_t row, uint8_t col)
{
	//Fetch word from layout array in program space
	// using pgm macro, and return as keycode
	uint16_t aWord = pgm_read_word(&(layout[current_layer][(row << ROWSHIFT)|col]));
	return (keycode)aWord;
}