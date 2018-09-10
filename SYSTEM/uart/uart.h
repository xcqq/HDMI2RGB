#ifndef __USART_H
#define __USART_H
#include "stdio.h"

void UARTInit(USART_TypeDef *uart_num, uint32_t baud);
void UARTSend(USART_TypeDef *uart_num, uint8_t *send_data, uint16_t len);
void UARTSetCallback(USART_TypeDef *uart_num, void (*callback)(uint8_t rec_data));

#endif
