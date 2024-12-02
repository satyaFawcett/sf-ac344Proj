/*
 * button.c
 *
 *  Created on: Nov 26, 2024
 *      Authors: Satya Fawcett, Aidan Catlin
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>
#include "sf344fun.h"
#include "delay.h"

#define debounce 100000

void button_init(void) {
	/*Description:
	 *Sets up the button on the board to trigger an interrupt, as well as for an external button connected to PC10 if desired
	 */

	//board button init
	enable_GPIO_clock(2); //GPIOC clock on
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //SYSCFG clock on
	GPIOC->MODER &= ~GPIO_MODER_MODE13; // PC13 to input
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_1; // PC13 to pull down

	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13; //Map EXTI line 13 to PC
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	EXTI->FTSR1 |= EXTI_FTSR1_FT13; //Set line 13 to falling edge trigger
	EXTI->IMR1 |= EXTI_IMR1_IM13; //Unmask interrupt event for line 13
	NVIC_SetPriority(TIM4_IRQn, 1);			// Set interrupt priority
	NVIC_EnableIRQ(EXTI15_10_IRQn); // enable interrupt handler for 15

	//external button init
	GPIOC->MODER &= ~GPIO_MODER_MODE10; // PC10 to input
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD10;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPD10_1; // PC10 to pull down

	SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI10; //Map EXTI line 10 to PC
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PC;
	EXTI->FTSR1 |= EXTI_FTSR1_FT10; //Set line 10 to falling edge trigger
	EXTI->IMR1 |= EXTI_IMR1_IM10; //Unmask interrupt event for line 10
	NVIC_EnableIRQ(EXTI15_10_IRQn); // enable interrupt handler for 10 to 15
}

// Interrupt handler for EXTI lines 10 to 15
void EXTI15_10_IRQHandler(void) {
	//blue button pressed
	if((EXTI->PR1 & EXTI_PR1_PIF13) != 0){
		//no debounce for board button

		TIM3->CR1 &= ~TIM_CR1_CEN; //Disable the output timer (TIM3)
		TIM3->ARR = TIM4->CNT;	   //set the output timer's ARR to the current count of the input timer (TIM4)
		TIM3->CR1 |= TIM_CR1_CEN;  //Re enable the output timer (TIM3)
		//set both input and output timers back to 0
		TIM4->CNT = 0;
		TIM3->CNT = 0;

		EXTI->PR1 = EXTI_PR1_PIF13; //clear pending flag
	}
	//button connected to PC10 pressed
	if((EXTI->PR1 & EXTI_PR1_PIF10) != 0){
		delay(debounce); //debounce for the external

		TIM3->CR1 &= ~TIM_CR1_CEN; //Disable the output timer (TIM3)
		//set the output timer's ARR to the current count of the input timer (TIM4) - (the #of debounce ticks/the timers prescaler)
		TIM3->ARR = TIM4->CNT - (debounce/15999);
		TIM3->CR1 |= TIM_CR1_CEN;  //Re enable the output timer (TIM3)
		//set both input and output timers back to 0
		TIM4->CNT = 0;
		TIM3->CNT = 0;

		EXTI->PR1 = EXTI_PR1_PIF10; //clear pending flag
	}

}
