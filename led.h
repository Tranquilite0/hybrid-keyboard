#ifndef led_h__
#define led_h__
#include <stdint.h>
//Bit shift values for keyboard lock bits
#define NUM_LOCK	0
#define CAPS_LOCK	1
#define SCROLL_LOCK	2

//LEDs are given friendly names
#define LED1 6 //LED1 is on pin D6
#define LED2 7 //LED2 is on pin D7

void led_init(void);
void update_leds(uint8_t);
#endif