/*
 * buzzer.c
 *
 *  Created on: Nov 6, 2024
 *      Authors: Satya Fawcett, Aidan Catlin
 *      Modified code from Satya's lab 5, ended up not using, but left in for potential of revisiting
 */

#include "stm32l476xx.h"
#include "sf344fun.h"
#include "music.h"
#include "delay.h"

//constants
const unsigned int freq[] = {100, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587};
#define BUZZER_PIN 10;

void buzzer_init(){
	/*Description:
	 *Sets up PA10 as output
	 */
	enable_GPIO_clock(0); //enable GPIOA clock
	GPIOA->MODER &= ~GPIO_MODER_MODE10;
	GPIOA->MODER |= GPIO_MODER_MODE10_0; // set PA10 to output
}

void playnote(struct note n) {
	/*Description:
	 * Uses a systick delay to rapidly toggle PA10 to play notes
	 */
	for (int i = 0; i < (n.duration * freq[n.notenum]) / 8; i++) {
		GPIOA->ODR ^= 1 << BUZZER_PIN; // Toggle buzzer
		delay(500000 / freq[n.notenum]); // Half period
		GPIOA->ODR ^= 1 << BUZZER_PIN; // Toggle buzzer
		delay(500000 / freq[n.notenum]);// Half period
	}
}

void playsong(const struct song *s) {
	/*Description:
	 * Takes an array of notes and plays them in sequence
	 */
	for (int i = 0; i < s->numnotes; i++) {
		playnote(s->thenotes[i]);
	}
}
