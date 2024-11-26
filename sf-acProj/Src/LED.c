/*
 * LED.c
 *
 *  Created on: Nov 6, 2024
 *      Author: fawcets
 */

#include "stm32l476xx.h"

void LED_init(){
	/*Description:
	 *
	 */
	enable_GPIO_clock(0); //enable GPIOA clock
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	GPIOA->MODER |= GPIO_MODER_MODE5_0; // set PA5 to output
}
void toggle_LED(){
	/*Description:
	 *
	 */
	GPIOA->ODR ^= GPIO_ODR_OD5;
}
