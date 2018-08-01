#ifndef __HW3_IMAGES_H__
#define __HW3_IMAGES_H__

#include <stdint.h>
#include <stdio.h>

#define       PACMAN_HEIGHT 	32	// height of pacman image in pixels
#define       PACMAN_WIDTH  	32	// width of pacman image in pixels
#define				WALL_HEIGHT			62	// height of wall image in pixels
#define				WALL_WIDTH			16	// width of wall image in pixels
#define				GND_HEIGHT  		70	// height of the ground in pixels
#define				GND_WIDTH				COLS	 // width of the ground in pixels
#define       PACMAN_HEIGHT_DUCK 	17 // height of ducking pacman in pixels
#define				LEDGE_HEIGHT  	6		// height of the ledge in pixels
#define				LEDGE_WIDTH			32	// width of the ledge in pixels
#define				GHOST_HEIGHT  	65	// height of the ghost in pixels
#define				GHOST_WIDTH			24	// width of the ghost in pixels
#define				BULLET_HEIGHT  	9		// height of the bullet in pixels
#define				BULLET_WIDTH		48	// width of the bullet in pixels
#define				FLAG_HEIGHT  		30	// height of the flag in pixels
#define				FLAG_WIDTH			24	// width of the flag in pixels

//externs for all the bitMaps
extern const uint8_t pacmanBitMap[];
extern const uint8_t ledgeBitMap[];
extern const uint8_t wallBitMap[];
extern const uint8_t ghostBitMap[];
extern const uint8_t groundBitMap[];
extern const uint8_t pacmanDuckBitMap[];
extern const uint8_t bulletBitMap[];
extern const uint8_t flagBitMap[];

#endif