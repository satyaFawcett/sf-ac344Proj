
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

const struct song marylamb = {
	26,
	{
		{4,3}, {2,1}, {0,2}, {2,2}, {4,2}, {4,2}, {4,4},
		{2,2}, {2,2}, {2,4}, {4,2}, {7,2}, {7,4}, {4,3},
		{2,1}, {0,2}, {2,2}, {4,2}, {4,2}, {4,2}, {4,2},
		{2,2}, {2,2}, {4,2}, {2,2}, {0,8}
	}
};

const struct song ironman = {
	14,
	{
		{0,4}, {2,4}, {2,2}, {3,2}, {3,4}, {6,1}, {5,1},
		{6,1}, {5,1}, {6,2}, {2,2}, {2,2}, {3,2}, {3,4}
	}
};

const struct note bass = {0, 2};

volatile int button_pressed = 0;
volatile int timeout = 0;
volatile int beat = 0;

int main(void)
{

  /* USER CODE BEGIN 1 */
//	System_Clock_Init();
	SysTick_Init(4);
	LED_init();
	button_init();

	buzzer_init();


  /* Infinite loop */
  while (1){
	  //execute if button pressed
	  if(button_pressed){
		  toggle_LED();
		  playnote(bass);
		  toggle_LED();
		  button_pressed = 0;
	  }
  }
  /* USER CODE END 3 */
}
