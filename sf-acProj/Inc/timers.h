/*

 * inputTimer.h

 *

 *  Created on: Nov 26, 2024

 *      Author: aidan

 */



#ifndef INPUTTIMER_H_

#define INPUTTIMER_H_


// Initialize TIM4 initialization function

void TIM4_Init();

// Initialize interrupt handler

void TIM4_IRQHandler();

// Initialize get_counterVal function

int get_counterVal();

// Initialize reset_counterVal function

void reset_counterVal();

void TIM3_Init();

void arr_set(int s);

#endif /* INPUTTIMER_H_ */


