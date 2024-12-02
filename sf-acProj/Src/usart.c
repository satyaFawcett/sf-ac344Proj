/*
 * usart.c
 *
 *  Created on: Dec 1, 2024
 *      Author: aidan
 */
#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

#define BufferSize 32
uint8_t buffer[BufferSize];

int ARR;
float period;
float BPM;

// Function for initializing the GPIO pins for USART2 transmission and reception
void UART2_GPIO_Init(void){
	// Turn on clock for A
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	//Configure GPIOA pins 2 and 3 as alternative function
	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	GPIOA->MODER |= GPIO_MODER_MODE2_1;		// (USART2_TX)
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	GPIOA->MODER |= GPIO_MODER_MODE3_1;

	//Set PA2 to AF7
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2;
	GPIOA->AFR[0] |= 0x7 << GPIO_AFRL_AFSEL2_Pos;

	//Set PA3 to AF7
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL3);
	GPIOA->AFR[0] |= 0x7 << GPIO_AFRL_AFSEL3_Pos;

	// Set GPIOA speed to High speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;			// Set PA2 to high speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;			// Set PA3 to high speed

	//Set pull-up/pull-down resistors to pull-up
	GPIOA->PUPDR &= ~(3 << (2*2));
	GPIOA->PUPDR |= (1 << (2*2));
	GPIOA->PUPDR &= ~(3 << (2*3));
	GPIOA->PUPDR |= (1 << (2*3));

	// Set output type to Push-Pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_ODR_2;			// Clear bits for PA2 in OTYPER
	GPIOA->OTYPER &= ~GPIO_OTYPER_ODR_3;			// Clear bits for PA3 in OTYPER

}

void USART_Init(USART_TypeDef * USARTx){
	// Disable USART
	USARTx->CR1 &= ~USART_CR1_UE;

	// Configure Word Length
	// Set data Length to 8 bits (00 = 8 data bits, 01 = 9 data bits, 10 = 7 data bits)
	USARTx->CR1 &= ~USART_CR1_M;

	// No parity
	USARTx->CR1 &= ~USART_CR1_PCE;

	// Configure 16x over-sampling
	USARTx->CR1 &= ~USART_CR1_OVER8;

	// Select 1 stop bit
	// 00 = 1 stop bit, 01 = 0.5 stop bit, 10 = 2 stop bits, 11 = 1.5 stop bits
	USARTx->CR2 &= ~USART_CR2_STOP;

	// Set Baud rate to 9600 using APB frequency (16 MHz)
	USARTx->BRR = 0x683;

	// Enable transmission and reception
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);

	//Enable USART
	USARTx->CR1 |= USART_CR1_UE;

	// Verify that USART is ready for transmission
	//TEACK: Transmit enable acknowledge flag. Hardware sets or resets it.
	while ((USARTx->ISR & USART_ISR_TEACK) == 0);

	// Verify that USART is ready for reception
	// REACK: Receive enable acknowledge flag. Hardware sets or resets it.
	while ((USARTx->ISR & USART_ISR_REACK) == 0);
}

// Function for initializing USART2 and configures UART communication
void UART2_Init(void){
	// Enable full access to the Co-processor Access Control Register for Floating Point Unit
	SCB->CPACR |= ((3UL << (10 * 2)) | (3UL << (11 * 2)));
	// Enable the clock for the USART2 peripheral
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
	// Select the system clock as the clock source
	RCC->CCIPR &= ~RCC_CCIPR_USART2SEL;
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
	// Initialize the GPIO pins and the USART peripheral
	UART2_GPIO_Init();
	USART_Init(USART2);

	while(!(USART2->ISR & USART_ISR_TEACK));
	while(!(USART2->ISR & USART_ISR_REACK));
}

// USART_Write function writes data from a buffer to a UART
void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes){
	for(int i = 0; i < nBytes; i++){
		while (!(USARTx->ISR & USART_ISR_TXE));		// Wait until hardware sets TXE
		USARTx->TDR = buffer[i];					// Writing to TDR clears TXE flag
		// Wait until TC bit is set. TC is set by hardware and cleared by software.
		while (!(USARTx->ISR & USART_ISR_TC));		// TC: Transmission complete flag
		USARTx->ICR |= USART_ICR_TCCF;				// TCCF: Transmission complete clear flag
	}
}

void printBPM(void){
	ARR = TIM3->ARR;
	period = (ARR+1)/1000.0;
	BPM = 60/period;

	int n;		// initialize n, this will store the length of the formatted string

//	n = sprintf((char *)buffer, "ARR = %d\t", ARR);
	n = sprintf((char *)buffer, "BPM = %f\r\n", BPM);

	// Send the string over UART
	USART_Write(USART2,buffer,n);
}
