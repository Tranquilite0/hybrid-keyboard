#ifndef bluefruit_h__
#define bluefruit_h__

//Bluefruit IO pin macros
#define BF_RESET_ON		(PORTF &= ~(1<<6)) //Active low signal
#define BF_RESET_OFF	(PORTF |= (1<<6))
#define BF_RESET_CONFIG	(DDRF |= (1<<6))
#define BF_RESET_READ   (PINF & (1<<6))
#define BF_PAIR_ON		(PORTF |= (1<<7)) //Active High signal
#define BF_PAIR_OFF		(PORTF &= ~(1<<7))
#define BF_PAIR_CONFIG	(DDRF |= (1<<7))
#define BF_PAIR_READ	(PINF & (1<<7))

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

//Function prototypes
void bluefruit_init(void);
void bluefruit_disable(void);
uint8_t bluefruit_configured(void);
void bluefruit_keyboard_set_report(keyboard_report*);
int8_t bluefruit_keyboard_send(void);
void bluefruit_check_uart(void);


#endif