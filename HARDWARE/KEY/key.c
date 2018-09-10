#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/*key name | port | pin*/
e_key_pin_mode_t key_list[] = {
	{key_num_poweron,GPIOB,GPIO_Pin_14},
	{key_num_dlp_mode,GPIOB,GPIO_Pin_15},
	{key_num_end},
};

//key driver here
void KeyInit(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t i;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	for (i = 0; key_list[i].key_num != key_num_end;i++)
	{
		GPIO_InitStructure.GPIO_Pin  = key_list[i].key_pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(key_list[i].key_port, &GPIO_InitStructure);
	}

}
e_key_num_t KeyScan(void)
{
	uint8_t i;
	for (i = 0; key_list[i].key_num != key_num_end;i++)
	{

		/*key press*/
		if(GPIO_ReadInputDataBit(key_list[i].key_port,key_list[i].key_pin)==0)
		{
			key_list[i].key_state = 1;
		}
		/*key release*/
		else
		{
			if(key_list[i].key_state == 1)
			{
				key_list[i].key_state = 0;
				return key_list[i].key_num;
			}
		}
	}
	return key_num_end;
}
