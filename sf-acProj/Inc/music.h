/*
 * main.h
 *
 *  Created on: Nov 8, 2024
 *      Authors: Satya Fawcett, Aidan Catlin
 */

#ifndef MUSIC_H_
#define MUSIC_H_

//structs definitions

//Note has an index which corresponds to a frequency defined in buzzer, and a duration in 1/8th of a second
struct note {
	unsigned char notenum; // Frequency index
	unsigned char duration; // Duration in 1/8 of a second
};

//song the total number of notes to play, and an array of the actual notes
struct song {
	unsigned char numnotes; // Number of notes in the song
	const struct note thenotes[30]; // Array of notes
};

#endif /* MUSIC_H_ */
