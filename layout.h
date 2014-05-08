#ifndef layout_h__
#define layout_h__
#include <stdint.h>

#define NUMLAYERS 8 //Not sure if needed yet

//Keycode structure
//Either a 16bit unsigned integer, or seperate keytype and keycode
typedef union
{
	uint16_t raw;
	struct 
	{
		uint8_t code;
		uint8_t type;
	};
}	__attribute__ ((__packed__)) keycode;

void set_current_layer(uint8_t);
uint8_t get_current_layer(void);
keycode get_keycode(uint8_t,uint8_t);

//Keycode defines

//TYPE 255: Miscelaneous
#define TYPE_MISC			0xFF
#define JMP_BOOT			0xFF00 //Jump to bootloader
#define CODE_JMP_BOOT		0x00
#define BR_UP				0xFF01 //Increase LED brightness
#define CODE_BR_UP			0x01
#define BR_DOWN				0xFF02 //Decrease LED brightness
#define CODE_BR_DOWN		0x02

//TYPE 5: Layer Toggle
#define TYPE_TOGGLE			0x05
#define TLAYER_0			0x05
#define TLAYER_1			0x0501
#define TLAYER_2			0x0502
#define TLAYER_3			0x0503
#define TLAYER_4			0x0504
#define TLAYER_5			0x0505
#define TLAYER_6			0x0506
#define TLAYER_7			0x0507

//TYPE 4: Momentary Layer Actuation
#define TYPE_MOMENTARY 		0x04
#define MLAYER_0			0x0400
#define MLAYER_1			0x0401
#define MLAYER_2			0x0402
#define MLAYER_3			0x0403
#define MLAYER_4			0x0404
#define MLAYER_5			0x0405
#define MLAYER_6			0x0406
#define MLAYER_7			0x0407

//TYPE 3: Reserved for Mouse keys
#define TYPE_MOUSE   		0x03
//TYPE 2: Reserved for Media keys
#define TYPE_MEDIA   		0x02

//TYPE 1: Keyboard modifiers
#define TYPE_MOD   		0x01
#define KB_CTRL			0x0101
#define KB_SHIFT		0x0102
#define KB_ALT			0x0104
#define KB_GUI			0x0108
#define KB_LEFT_CTRL	0x0101
#define KB_LEFT_SHIFT	0x0102
#define KB_LEFT_ALT		0x0104
#define KB_LEFT_GUI		0x0108
#define KB_RIGHT_CTRL	0x0110
#define KB_RIGHT_SHIFT	0x0120
#define KB_RIGHT_ALT	0x0140
#define KB_RIGHT_GUI	0x0180
//Space friendly Versions
#define KB_LCTRL		0x0101
#define KB_LSHFT		0x0102
#define KB_LALT			0x0104
#define KB_LGUI			0x0108
#define KB_RCTRL		0x0110
#define KB_RSHFT		0x0120
#define KB_RALT			0x0140
#define KB_RGUI			0x0180

//TYPE 0: Keyboard keycodes
#define TYPE_KEY    0
#define KB_NONE     0
#define KB_A		4
#define KB_B		5
#define KB_C		6
#define KB_D		7
#define KB_E		8
#define KB_F		9
#define KB_G		10
#define KB_H		11
#define KB_I		12
#define KB_J		13
#define KB_K		14
#define KB_L		15
#define KB_M		16
#define KB_N		17
#define KB_O		18
#define KB_P		19
#define KB_Q		20
#define KB_R		21
#define KB_S		22
#define KB_T		23
#define KB_U		24
#define KB_V		25
#define KB_W		26
#define KB_X		27
#define KB_Y		28
#define KB_Z		29
#define KB_1		30
#define KB_2		31
#define KB_3		32
#define KB_4		33
#define KB_5		34
#define KB_6		35
#define KB_7		36
#define KB_8		37
#define KB_9		38
#define KB_0		39
#define KB_ENTER	40	
#define KB_ESC		41
#define KB_BKSPC	42	
#define KB_TAB		43
#define KB_SPACE	44	
#define KB_MINUS	45
#define KB_EQUAL	46
#define KB_LBRCE	47
#define KB_RBRCE	48
#define KB_BSLSH	49
#define KB_NUMBER	50 // Non-US # and ~ 
#define KB_SMCLN	51
#define KB_QUOTE	52
#define KB_TILDE	53
#define KB_COMMA	54
#define KB_DOT		55
#define KB_SLASH	56
#define KB_CAPLK	57
#define KB_F1		58
#define KB_F2		59
#define KB_F3		60
#define KB_F4		61
#define KB_F5		62
#define KB_F6		63
#define KB_F7		64
#define KB_F8		65
#define KB_F9		66
#define KB_F10		67
#define KB_F11		68
#define KB_F12		69
#define KB_PSCRN	70		
#define KB_SCRLK	71		
#define KB_PAUSE	72
#define KB_INS		73	
#define KB_HOME		74
#define KB_PGUP		75
#define KB_DEL		76
#define KB_END		77
#define KB_PGDN		78	
#define KB_RIGHT	79
#define KB_LEFT		80
#define KB_DOWN		81
#define KB_UP		82
#define KB_NUMLK	83
#define KP_SLASH	84	
#define KP_ASTRX	85	
#define KP_MINUS	86	
#define KP_PLUS		87	
#define KP_ENTER	88	
#define KP_1		89
#define KP_2		90
#define KP_3		91	
#define KP_4		92	
#define KP_5		93	
#define KP_6		94	
#define KP_7		95	
#define KP_8		96	
#define KP_9		97	
#define KP_0		98		
#define KP_DOT		99	

#define KB_PIPE 	100
#define KB_APP		101
#define KB_POWER 	102
#define KP_EQUAL	103

#define KB_F13 104
#define KB_F14 105
#define KB_F15 106
#define KB_F16 107
#define KB_F17 108
#define KB_F18 109
#define KB_F19 110
#define KB_F20 111
#define KB_F21 112
#define KB_F22 113
#define KB_F23 114
#define KB_F24 115

#define KB_EXECUTE 116
#define KB_HELP 117
#define KB_MENU 118
#define KB_SELECT 119
#define KB_STOP 120
#define KB_AGAIN 121

#define KB_UNDO 122
#define KB_CUT 123
#define KB_COPY 124
#define KB_PASTE 125
#define KB_FIND 126

#define KB_MUTE 127
#define KB_VOLUMEUP 128
#define KB_VOLUMEDOWN 129

#define KB_LOCKINGCAPSLOCK 130
#define KB_LOCKINGNUMLOCK 131
#define KB_LOCKINGSCROLLLOCK 132

#define KP_COMMA 133
#define KP_EQUALSIGN 134

#define KB_INTERNATIONAL1 135
#define KB_INTERNATIONAL2 136
#define KB_INTERNATIONAL3 137
#define KB_INTERNATIONAL4 138
#define KB_INTERNATIONAL5 139
#define KB_INTERNATIONAL6 140
#define KB_INTERNATIONAL7 141
#define KB_INTERNATIONAL8 142
#define KB_INTERNATIONAL9 143

#define KB_LANG1 144
#define KB_LANG2 145
#define KB_LANG3 146
#define KB_LANG4 147
#define KB_LANG5 148
#define KB_LANG6 149
#define KB_LANG7 150
#define KB_LANG8 151
#define KB_LANG9 152

#define KB_ALTERNATE_ERASE 153
#define KB_SYSREQ 154
#define KB_CANCEL 155
#define KB_CLEAR 156
#define KB_PRIOR 157
#define KB_RETURN 158
#define KB_SEPARATOR 159
#define KB_OUT 160
#define KB_OPER 161
#define KB_CLEAR_AGAIN 162
#define KB_CRSEL 163
#define KB_EXSEL 164

#define KB_RESERVED2 165-175

#define KP_00 176
#define KP_000 177

#define KB_THOUSANDS_SEPARATOR 178
#define KB_DECIMAL_SEPARATOR 179
#define KB_CURRENCY_UNIT 180
#define KB_CURRENCY_SUBUNIT 181

#define KP_LEFT_PAREN 182
#define KP_RIGHT_PAREN 183
#define KP_LEFT_BRACE 184
#define KP_RIGHT_BRACE 185

#define KP_TAB 186
#define KP_BACKSPACE 187

#define KP_A 188
#define KP_B 189
#define KP_C 190
#define KP_D 191
#define KP_E 192
#define KP_F 193

#define KP_XOR 194
#define KP_POWER 195
#define KP_MOD 196
#define KP_LESS 197
#define KP_GREATER 198
#define KP_BIT_AND 199
#define KP_AND 200
#define KP_BIT_OR 201
#define KP_OR 202
#define KP_COLON 203
#define KP_NUMBER 204
#define KP_SPACE 205
#define KP_AT 206
#define KP_NOT 207

#define KP_MEMORY_STORE 208
#define KP_MEMORY_RECALL 209
#define KP_MEMORY_CLEAR 210
#define KP_MEMORY_ADD 211
#define KP_MEMORY_SUBTRACT 212
#define KP_MEMORY_MULTIPLY 213
#define KP_MEMORY_DIVIDE 214
#define KP_PLUSMINUS 215

#define KP_CLEAR 216
#define KP_CLEAR_ENTRY 217
#define KP_BINARY 218
#define KP_OCTAL 219
#define KP_DECIMAL 220
#define KP_HEXADECIMAL 221

#define KB_RESERVED3 222-223

#endif