/*
 * sys_init.c
 *
 *  Created on: Nov 6, 2024
 *      Author: fawcets
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

void System_Clock_Init(){
	/*	Description:
	 *sets the system clock to use HSI16
	 */

		uint32_t HSITrim = 16;

		//flash wait states
		FLASH->ACR &= ~FLASH_ACR_LATENCY;
		FLASH->ACR |= 0b100;

		//Configure HSI
		RCC->CR |= RCC_CR_HSION;
		while((RCC->CR & RCC_CR_HSIRDY) == 0); //wait for HSIRDY to be cleared
		//Calibrate HSI16
		RCC->ICSCR &= ~RCC_ICSCR_HSITRIM;
		RCC->ICSCR |= HSITrim << RCC_ICSCR_HSITRIM_Pos;
		//select HSI as system clock
		RCC->CFGR &= ~RCC_CFGR_SW;
		RCC->CFGR |= RCC_CFGR_SW_HSI;
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // wait till system clock is selected
}

void SysTick_Init(int ticks){
	/*Description:
	 *
	 */

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable SysTick
	SysTick->LOAD = ticks - 1; // Set reload register
	// Set interrupt priority of SysTick to least urgency (i.e., largest priority value)
	NVIC_SetPriority (SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0; // Reset the SysTick counter value
	// Select processor clock to internal clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	// Enables SysTick interrupt
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	// Enable SysTick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
