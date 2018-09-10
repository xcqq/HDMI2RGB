#include "sys.h"
#include "uart.h"

void (*uart1_callback)(uint8_t);
void (*uart2_callback)(uint8_t);

#if 0
#pragma import(__use_no_semihosting)             
             
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
   
_sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);
    USART1->DR = (u8) ch;      
	return ch;
}
#endif


void UARTInit(USART_TypeDef *uart_num,uint32_t baud)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

   
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
   
    USART_Cmd(USART1, ENABLE);

}

void UARTSend(USART_TypeDef *uart_num,uint8_t *send_data,uint16_t len)
{
	uint16_t i = 0;
	if(uart_num==USART1)
	{
		while((USART1->SR&0X40)==0);
		for (i = 0; i < len;i++)
		{
			USART1->DR = *(send_data + i);
		}
	}
	else if (uart_num==USART2)
	{
		while((USART2->SR&0X40)==0);
		for (i = 0; i < len;i++)
		{
			USART2->DR = *(send_data + i);
		}
	}
}

void UARTSetCallback(USART_TypeDef *uart_num,void (*callback)(uint8_t rec_data))
{
	if(uart_num==USART1)
	{
		uart1_callback = callback;
	}
	else if(uart_num==USART2)
	{
		uart2_callback = callback;
	}
}

void USART1_IRQHandler(void)
{
	uint8_t rec_data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		rec_data =USART_ReceiveData(USART1);
		if(uart1_callback!=NULL)
			uart1_callback(rec_data);
	} 
} 
 

void USART2_IRQHandler(void)
{
	uint8_t rec_data;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		rec_data =USART_ReceiveData(USART2);
		if(uart2_callback!=NULL)
			uart2_callback(rec_data);
	}
}