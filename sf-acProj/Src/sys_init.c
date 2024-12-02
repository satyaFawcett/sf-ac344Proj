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
 *
 */

	uint32_t HSITrim = 16;

	//Setting Flash Wait States
	FLASH->ACR &= ~FLASH_ACR_LATENCY; //Clearing latency bits
	FLASH->ACR |= 0b100; //Setting four wait states

	//Configuring HSI
	RCC->CR |= (0b1 << 8); //Setting the HSI oscillator on
	while((RCC->CR & (0b1 << 10)) == 0); //waiting for the oscillator to be ready before moving on

	//Calibrating HSI16 in internal clock sources calibration register
	HSITrim = 16; //Trimming value which is added to HSICAL[7:0]
	RCC->ICSCR &= ~RCC_ICSCR_HSITRIM; //Clearing HSITRIM bits
	RCC->ICSCR |= HSITrim << 24; //Adjusts the HSI calibration value
	//This factory calibration value plus the HSITrim value will be loaded in

	//Setting HSI16 as system clock
	RCC->CFGR &= ~RCC_CFGR_SW; //Clearing system clock selection bits
	RCC->CFGR |= (0b01); //Choosing the HSI16 as the system clock

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
