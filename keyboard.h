#ifndef keyboard_h__
#define keyboard_h__
//Number of microseconds to delay to allow for switch debouncing
//5 is recommended, but increase this value if you get repeated keypreses
#define DEBOUNCE_TIME 5
#include <stdint.h>
#include "layout.h"

//Boolean defines for keystates
#define KEY_IS_DOWN 	1
#define KEY_IS_UP 		0

//Function Prototypes
void keyboard_init(void);
void keyboard_main(void);
void key_execute(keycode, uint8_t);
void add_key(uint8_t aKey);
void del_key(uint8_t aKey);
void add_mod(uint8_t aMod); 
void del_mod(uint8_t aMod);
void clear_keyboard(void);
void keyboard_send_report(void);
void jump_bootloader(void);

#ifndef keyboard_report__
#define keyboard_report__
#define KEYS_PER_REPORT 6 //Number of keys in a USB/Bluetooth report
//Keyboard report structure
typedef struct
{
	uint8_t mods; // Bitfield containing keyboard modifiers
	uint8_t keys[KEYS_PER_REPORT]; //Up to 6 keys per report
} keyboard_report;
#endif

#endif