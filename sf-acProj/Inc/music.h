/*
 * main.h
 *
 *  Created on: Nov 8, 2024
 *      Author: fawcets
 */

#ifndef MUSIC_H_
#define MUSIC_H_

//structs
struct note {
	unsigned char notenum; // Frequency index
	unsigned char duration; // Duration in 1/8 of a second
};

struct song {
	unsigned char numnotes; // Number of notes in the song
	const struct note thenotes[30]; // Array of notes
};

#endif /* MUSIC_H_ */
