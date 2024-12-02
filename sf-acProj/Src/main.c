/*
 * button.c
 *
 *  Created on: Nov 18, 2024
 *      Authors: Satya Fawcett, Aidan Catlin
 */




/* Includes ------------------------------------------------------------------*/
#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

/* Private includes ----------------------------------------------------------*/
#include "sf344fun.h"
#include "sys_init.h"
//#include "delay.h"
#include "LED.h"
//#include "buzzer.h"
#include "music.h"
#include "button.h"
#include "timers.h"
#include "usart.h"


int main(void)
{
/*Description:
 * Main just initializes everything, rest is done in interupts
 */

	System_Clock_Init();
	LED_init();
	button_init();
	TIM4_Init();
	TIM3_Init();
	UART2_Init();

  /* Infinite loop */
  while (1){
	  //Do nothing

  }

}
