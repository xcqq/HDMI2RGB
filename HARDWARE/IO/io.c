#include "stm32f10x.h"
#include "io.h"
#include "sys.h" 

/*io name | port | pin | mode*/
e_io_pin_mode_t io_list[] = {
	{io_num_hdmi_rst,GPIOB,GPIO_Pin_1,GPIO_Mode_Out_PP},
	{io_num_hdmi_int,GPIOB,GPIO_Pin_2,GPIO_Mode_IN_FLOATING},
	{io_num_dlp_en,GPIOA,GPIO_Pin_8,GPIO_Mode_Out_PP},
	{io_num_end},
};

//key driver here
void IOInit(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t i;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	for (i = 0; io_list[i].io_num != io_num_end;i++)
	{
		GPIO_InitStructure.GPIO_Pin  = io_list[i].io_pin;
		GPIO_InitStructure.GPIO_Mode = io_list[i].io_mode;
		GPIO_Init(io_list[i].io_port, &GPIO_InitStructure);
	}

}

void IOSet(e_io_num_t io_num,uint8_t state)
{
	GPIO_WriteBit(io_list[io_num].io_port,io_list[io_num].io_pin,state);
}

uint8_t IOGet(e_io_num_t io_num)
{
	GPIO_ReadInputDataBit(io_list[io_num].io_port, io_list[io_num].io_pin);
}