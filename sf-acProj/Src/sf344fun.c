/*
 * sf344fun.c
 *
 *  Created on: Oct 18, 2024
 *      Author: fawcets
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
			printf("enable_GPIO_clock error invalid input, please input lower case a-h \n");
			break;
	}
}

