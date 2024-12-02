/*
 * LED.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Satya Fawcett
 *      Directly coppied from Satya's lab 5
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>
#include "sf344fun.h"

void LED_init(){
	/*Description:
	 *Sets up PA5 as output
	 */
	enable_GPIO_clock(0); //enable GPIOA clock
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_0; // set PA5 to output
}
void toggle_LED(){
	/*Description:
	 *Toggles PA5
	 */
	GPIOA->ODR ^= GPIO_ODR_OD5;
}
