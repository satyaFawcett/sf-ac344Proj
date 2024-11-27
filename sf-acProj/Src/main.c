
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



const struct note bass = {0, 2};

volatile int button_pressed = 0;
volatile int timeout = 0;
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
		  last_count = get_counterVal();
		  reset_counterVal();
		  arr_set(last_count);
		  //play note and flash led
//		  toggle_LED();
//		  playnote(bass);
//		  toggle_LED();
//		  button_pressed = 0;
	  }

	  //execute if TIM3 overflows
	  if(beat){
		  //play note and flash led
		  toggle_LED();
		  playnote(bass);
		  toggle_LED();
		  beat = 0;
	  }

	  //execute if timeout triggered
	  if(timeout){

	  }
  }
  /* USER CODE END 3 */
}
