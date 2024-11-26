/*
 * delay.c
 *
 *  Created on: Nov 6, 2024
 *      Author: fawcets
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

volatile int time_delay = 0;

void SysTick_Handler(){
	/*Description:
	 *
	 */
	if(time_delay > 0){
		time_delay--; //decrement time delay
	}
}

void delay(uint32_t nTime){
	/*Description:
	 *
	 */
	time_delay = nTime;
	while(time_delay > 0);
}
