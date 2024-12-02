/*
 * delay.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Satya Fawcett
 *      Directly copied from Satya's lab 5, ended up not using since it was only for the buzzer,
 *      but left in for revisiting
 */

#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

volatile int time_delay = 0;

void SysTick_Handler(){
	/*Description:
	 *Interupt handler for SysTick, decrements time_delay every tick
	 */
	if(time_delay > 0){
		time_delay--; //decrement time delay
	}
}

void delay(uint32_t nTime){
	/*Description:
	 *Busy wait delay for nTime # of ticks
	 */
	time_delay = nTime; //set global time_delay to nTime
	while(time_delay > 0); //busy wait until time_delay <= 0
}
