/*
 * sf344fun.c
 *
 *  Created on: Oct 18, 2024
 *      Author: Satya Fawcett
 *      Just contains a function to turn on GPIO clocks that I wrote at the beginning of the quarter,
 *      and have use in almost every lab since.
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

void enable_GPIO_clock(int port){
//takes integer between 0 and 7 and enables the corresponding GPIO port clock
//with A = 0, H = 7
	switch (port) {
		case 0:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			break;
		case 1:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			break;
		case 2:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
			break;
		case 3:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIODEN;
			break;
		case 4:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
			break;
		case 5:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOFEN;
			break;
		case 6:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOGEN;
			break;
		case 7:
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOHEN;
			break;
		default:
			//tell the user to input an integer from 0-7, will throw an error instead if printf is not enabled.
			printf("enable_GPIO_clock error invalid input, please input integer from 0-7 \n");
			break;
	}
}

