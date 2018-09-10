#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

typedef enum
{
    led_num_state=0,
    led_num_error,
    led_num_end
}e_led_num_t;

typedef struct  
{
	e_led_num_t led_num;
	GPIO_TypeDef *led_port;
	uint16_t led_pin;
}s_led_pin_mode_t;	

void LEDInit(void);
void LEDSet(e_led_num_t led_num, uint8_t state);

#endif
