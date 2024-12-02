/*
 * usart.h
 *
 *  Created on: Dec 1, 2024
 *      Author: aidan
 */

#ifndef USART_H_
#define USART_H_

void UART2_GPIO_Init(void);
void USART_Init(USART_TypeDef * USARTx);
void UART2_Init(void);
void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes);
void printBPM();

#endif /* USART_H_ */
