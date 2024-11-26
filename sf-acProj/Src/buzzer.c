/*
 * buzzer.c
 *
 *  Created on: Nov 6, 2024
 *      Author: fawcets
 */

#include "stm32l476xx.h"
#include "sf344fun.h"
#include "music.h"
#include "delay.h"

//constants
const unsigned int freq[] = {80, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587};
#define BUZZER_PIN 10;

void buzzer_init(){
	/*Description:
	 *
	 */
	enable_GPIO_clock(0); //enable GPIOA clock
	GPIOA->MODER &= ~GPIO_MODER_MODE10;
	GPIOA->MODER |= GPIO_MODER_MODE10_0; // set PA10 to output
}

void playnote(struct note n) {
	for (int i = 0; i < (n.duration * freq[n.notenum]) / 8; i++) {
		GPIOA->ODR ^= 1 << BUZZER_PIN; // Toggle buzzer
		delay(500000 / freq[n.notenum]); // Half period
		GPIOA->ODR ^= 1 << BUZZER_PIN; // Toggle buzzer
		delay(500000 / freq[n.notenum]);
	}
	delay(0.5 * 125000); // Short delay between notes
}

void playsong(const struct song *s) {
	for (int i = 0; i < s->numnotes; i++) {
		playnote(s->thenotes[i]);
	}
}
