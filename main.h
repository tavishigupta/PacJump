// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "driver_defines.h"
#include "gpio_port.h"
#include "serial_debug.h"
#include "validate.h"

extern void initialize_serial_debug(void);
char alphabet[27] = { 'A','B','C','D','E','F','G','H','I','J',
											'K','L','M','N','O','P','Q','R','S','T',
											'U','V','W','X','Y','Z','!'};

//enumerator types
typedef enum {IDLE, JUMP, DUCK, SHOOT} action_type_t;
typedef enum {WALL, GHOST, LEDGE, FLAG} obstacle_type_t;
typedef enum 
{
  DEBOUNCE_ONE,
  DEBOUNCE_1ST_ZERO,
  DEBOUNCE_2ND_ZERO,
  DEBOUNCE_PRESSED
} DEBOUNCE_STATES;

typedef struct {
	action_type_t action;
	uint16_t x_loc;
	uint16_t y_loc;
} pacman_t;

typedef struct {
	uint16_t x_loc;
	uint16_t y_loc;
} bullet_t;

struct obstacle_t {
	obstacle_type_t type;
	uint16_t x_loc;
	uint16_t y_loc;
	struct obstacle_t *nxt;
};

typedef struct {
	char initials[4];
	uint16_t score;
} high_score_t;

#define SYSTICK_LOAD_VAL 5000
#define ADDR_START    256

//main functions
void redraw_all();
void redraw_pacman_jump();
void redraw_pacman_duck();
void redraw_pacman_shooting();
obstacle_type_t random_obstacle();
void update_obstacles();
void add_obstacle();
void remove_obstacle(
	struct obstacle_t *del_obstacle, 
	struct obstacle_t *prev_obstacle
);
void update_score();


#endif
