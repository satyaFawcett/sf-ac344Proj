/*
 * sys_init.c
 *
 *  Created on: Nov 6, 2024
 *      Author: fawcets
 */

#include "stm32l476xx.h"


void System_Clock_Init(){
/*	Description:
 *
 */

	uint32_t HSITrim = 16;

	//Set flash wait states
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
	//Configure HSI
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0); //wait for HSIRDY to be cleared
	//Calibrate HSI16
	RCC->ICSCR &= ~RCC_ICSCR_HSITRIM;
	RCC->ICSCR |= HSITrim << RCC_ICSCR_HSITRIM_Pos;
	//Disable PLL
	RCC->CR &= ~RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) == RCC_CR_PLLRDY); //wait till PLLRDY is cleared
	//Configure PLL to 80 MHz
	//f(sys) = f(VCO)/PLLR
	//80MHz = 160/2; f(VCO) = 160 PLLR = 2
	//f(VCO) = f(PLL input) * (PLLN/PLLM)
	//160MHz = 16MHz * (PLLN/PLLM)
	//PLLN/PLLM = 10 = 20/2; PLLN = 20 PLLM = 2
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= 20U << RCC_PLLCFGR_PLLN_Pos; //plln to 20
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= 1U << RCC_PLLCFGR_PLLM_Pos; //pllm to 2
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLR; //pllr to 2
	//set hsi as source for PLL
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
	//Enable PLLR output
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;
	//Enable the PLL
	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) == 0); //wait till PLLRDY is cleared
	//select PLL as system clock
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // wait till system clock is selected
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
