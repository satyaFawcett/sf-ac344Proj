/*
 * inputTimer.c
 *
 *  Created on: Nov 26, 2024
 *      Author: aidan
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

extern volatile int timeout;
extern volatile int beat;

// Function to read the current value of the counter
int get_counterVal(){
	return TIM4->CNT;		// Read the current counter value
}

// Function to reset the counter value to 0
void reset_counterVal(){
	TIM4->CNT = 0;		// Reset the counter value to 0
}

// Simple 1kHz up counting timer (input)
void TIM4_Init(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;		// Enable the TIM4 clock

	TIM4->CR1 &= ~TIM_CR1_CMS;					// Set the edge-aligned mode
	TIM4->CR1 &= ~TIM_CR1_DIR;					// Up-counting mode (default)

	// Set the PSC and ARR fields to achieve a 1kHz output
	TIM4->PSC = 79000;		// Pre-scaler to divide 16 MHz clock to 1 kHz
	TIM4->ARR = 2999;		// Auto-reload for 3-second interrupt

	TIM4->CR2 &= ~TIM_CR2_MMS;			// No master mode output

	TIM4->CCER = 0;						// Disable all output channels
	TIM4->CCMR1 = 0;					// Reset capture/compare mode registers

	TIM4->DIER |= TIM_DIER_UIE;			// Enable update interrupt

	NVIC_SetPriority(TIM4_IRQn, 1);			// Set interrupt priority
	NVIC_EnableIRQ(TIM4_IRQn);				// Enable TIM4 interrupt in NVIC

	// Enable the timer
	TIM4->CR1 |= TIM_CR1_CEN;
}

// Interrupt handler code for the counter reaching 3 seconds
void TIM4_IRQHandler(void){
	if (TIM4->SR & TIM_SR_UIF){		// Check if update interrupt flag
		TIM4->SR &= ~TIM_SR_UIF;	// Clear the interrupt flag
		TIM4->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
		timeout = 1;				// Set flag for timer disabled
	}
}

// Output timer to trigger buzzer
void TIM3_Init(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;		// Enable the TIM3 clock

	TIM3->CR1 &= ~TIM_CR1_CMS;					// Set the edge-aligned mode
	TIM3->CR1 &= ~TIM_CR1_DIR;					// Up-counting mode (default)

	// Set the PSC and ARR fields to achieve a 1kHz output
	TIM3->PSC = 79000;		// Pre-scaler to divide 16 MHz clock to 1 kHz
	TIM3->ARR = 2999;		// Auto-reload for 3-second interrupt

	TIM3->CR2 &= ~TIM_CR2_MMS;			// No master mode output

	TIM3->CCER = 0;						// Disable all output channels
	TIM3->CCMR1 = 0;					// Reset capture/compare mode registers

	TIM3->DIER |= TIM_DIER_UIE;			// Enable update interrupt

	NVIC_SetPriority(TIM3_IRQn, 1);			// Set interrupt priority
	NVIC_EnableIRQ(TIM3_IRQn);				// Enable TIM3 interrupt in NVIC

	// Enable the timer
	TIM3->CR1 |= TIM_CR1_CEN;
}

void arr_set(int s){
	TIM3->CR1 &= ~TIM_CR1_CEN;
	TIM3->ARR = s;
	TIM3->CR1 |= TIM_CR1_CEN;
}

// Interrupt handler code to set beat = 1 on overflow
void TIM3_IRQHandler(void){
	if (TIM3->SR & TIM_SR_UIF){		// Check if update interrupt flag
		TIM3->SR &= ~TIM_SR_UIF;	// Clear the interrupt flag
		beat = 1;
		// Set ARR to get_counterVal here? or assign in timer init?
	}
}

