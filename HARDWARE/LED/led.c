#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "led.h"

/*led name | port | pin*/
s_led_pin_mode_t led_list[] = {
	{led_num_state,GPIOB,GPIO_Pin_12},
	{led_num_error,GPIOB,GPIO_Pin_13},
	{led_num_end},
};

void LEDInit(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t i;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	for (i = 0; led_list[i].led_num != led_num_end;i++)
	{
		GPIO_InitStructure.GPIO_Pin  = led_list[i].led_pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(led_list[i].led_port, &GPIO_InitStructure);
	}
}
 
void LEDSet(e_led_num_t led_num,uint8_t state)
{
	if(state==1)
	{
    	GPIO_SetBits(led_list[led_num].led_port,led_list[led_num].led_pin);
	}
	else
	{
    	GPIO_ResetBits(led_list[led_num].led_port,led_list[led_num].led_pin);
	}
}
