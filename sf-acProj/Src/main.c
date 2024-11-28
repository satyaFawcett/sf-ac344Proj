
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "stm32l476xx.h"
#include<stdio.h>
#include<stdint.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sf344fun.h"
#include "sys_init.h"
#include "delay.h"
#include "LED.h"
#include "buzzer.h"
#include "music.h"
#include "button.h"
#include "timers.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FP */

/* USER CODE END FP */

#define offset 312

const struct note bass = {0, 2};

volatile int button_pressed = 0;
volatile int timeout = 1;
volatile int beat = 0;
int last_count = 0;

int main(void)
{

  /* USER CODE BEGIN 1 */
	System_Clock_Init();
	SysTick_Init(80);
	LED_init();
	button_init();
	buzzer_init();
	TIM4_Init();
	TIM3_Init();


  /* Infinite loop */
  while (1){
	  //execute if button pressed
	  if(button_pressed){
		  //execute if timeout triggered
		  if(timeout){
			  TIM4->CR1 |= TIM_CR1_CEN;	//Enable the timer
			  TIM4->CNT = 0;
			  timeout = 0;
		  }
		  else{
			  TIM3->CR1 &= ~TIM_CR1_CEN;
			  TIM3->ARR = TIM4->CNT - offset;
			  TIM3->CR1 |= TIM_CR1_CEN;


			  //play note and flash led
//	  		  toggle_LED();
//	  		  playnote(bass);
//	  		  toggle_LED();
		  }
		  TIM3->CNT = 0;
		  button_pressed = 0;
	  }

	  //execute if TIM3 overflows
	  if(beat){
		  //play note and flash led
		  toggle_LED();
		  playnote(bass);
		  toggle_LED();
		  beat = 0;
	  }

  }
  /* USER CODE END 3 */
}
