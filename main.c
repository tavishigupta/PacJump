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

#include "main.h"
#include "lcd.h"
#include "timers.h"
#include "ps2.h"
#include "eeprom.h"
#include "launchpad_io.h"
#include "HW3_images.h"
#include "io_expander.h"
#include "ece353_hw2_fonts.h"
#include "qei.h"
#include <stdio.h>
#include <string.h>

//ADC thresholds
#define ADC_MAX (0xFFF*3)/4
#define ADC_MIN 0xFFF/4

//universal ground position for game
#define GND_POS 		ROWS-GND_HEIGHT
#define BASE_SPEED	160

// Masks for io_expander interrupts
#define UP_BUTTON   0xE
#define DOWN_BUTTON_PRESSED 0xD
#define DOWN_BUTTON_DEBOUNCE 0xF
#define BULLET_BUTTON 0x7
#define BULLET_DEBOUNCE 0xF

char group[] = "Group29";
char individual_1[] = "Carter Swedal";
char individual_2[] = "Tavishi Gupta";

struct obstacle_t * head = NULL;
struct obstacle_t * tail = NULL;
uint8_t num_obstacles = 0;

//handler flags
volatile uint8_t speed = BASE_SPEED;
volatile bool redraw = false;
volatile bool up_button = false;
volatile bool down_button = false;
volatile bool bullet_button = false;
volatile bool joystick_int = true;
volatile bool game_over = false;
volatile bool sw1_pressed = false;
volatile bool read_qei = false;

//global flags
bool end_flag = false;
bool ducking = false;
bool ongoing_action = false;
bool game_winner = false;

//global vars
bullet_t bullet;
action_type_t pacManAction;
pacman_t pacman;
high_score_t scores[3];
uint8_t multiplier = 1;
uint8_t score_baseline = 0;
uint16_t score = 6500;
char buffer_str[6];
uint8_t finishing_place = 0;
uint8_t seed = 0;

//ps2 adc values and button flags
uint32_t ps2_x = 0x800;
uint32_t ps2_y = 0x800;
uint8_t ps2_up = false;
uint8_t ps2_down = false;
uint8_t ps2_left = false;
uint8_t ps2_right = false;

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
// 
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}

//*****************************************************************************
// 
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

void initialize_hardware(void)
{
	//allow for debugging and printf
	DisableInterrupts();
  init_serial_debug(true, true);
  EnableInterrupts();
	
	// setup lcd GPIO, config the screen, and clear it
  lcd_config_gpio();
	lcd_config_screen();
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	// setup the timers for the game clock
  SysTick_Config(SYSTICK_LOAD_VAL);
	
	// setup GPIO for IO expander to use interrupts
	io_expander_init();
	config_up_down_buttons();
	io_expander_en_interrupts();
	
	//setup eeprom 
	eeprom_init();
		
	//initialize the qudrature encoder
	qei0_init();
	
	// Setup ADC to convert on PS2 joystick using SS2 and interrupts
	gp_timer_config_32(TIMER0_BASE, TIMER_TAMR_TAMR_PERIOD, false, true);
	ps2_initialize();
	
	//setup switch1
	lp_io_init();
}

//from ICEs
bool sw1_debounce_fsm(void)
{
  static DEBOUNCE_STATES state = DEBOUNCE_ONE;
  bool pin_logic_level;
  
  pin_logic_level = lp_io_read_pin(SW1_BIT);
  
  switch (state)
  {
    case DEBOUNCE_ONE:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_1ST_ZERO;
      }
      break;
    }
    case DEBOUNCE_1ST_ZERO:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_2ND_ZERO;
      }
      break;
    }
    case DEBOUNCE_2ND_ZERO:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    case DEBOUNCE_PRESSED:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    default:
    {
      while(1){};
    }
  }
  
  if(state == DEBOUNCE_2ND_ZERO )
  {
    return true;
  }
  else
  {
    return false;
  }
}

//happens every 10ms
void SysTick_Handler()
{
	static int16_t count = 0;
	int val; 
  
	//create game clock based on speed
	if (count >= speed) {
		redraw = true;
		count = 0;
	}
	
	val = SysTick->VAL; //clear interrupt
	count++;
	seed++; //used to create random obstacles
}

void GPIOF_Handler() {
	uint8_t readval;

	//read in the io_expander button statuses
	readval = io_expander_read_reg(MCP23017_INTCAPB_R);
	
	//set appropriate flag true based on the button being pressed
	if (readval == BULLET_BUTTON && !ongoing_action)
		bullet_button = true;
	else if (readval == BULLET_DEBOUNCE && bullet_button)
		bullet_button = false;
	else if (readval == UP_BUTTON && !ongoing_action)
		up_button = true;
	else if (readval == DOWN_BUTTON_PRESSED && !ongoing_action)
		down_button = true;
	else if (readval == DOWN_BUTTON_DEBOUNCE && down_button)
		down_button = false;
	
	//clear gpiof interrupt
	GPIOF->ICR |= PF0;
}
void TIMER0A_Handler() {
	//start the conversion to get new plane position
	start_adc_conversion(PS2_ADC_BASE, PS2_X_ADC_CHANNEL, PS2_Y_ADC_CHANNEL);

	read_qei = true;

  if (sw1_debounce_fsm())
		sw1_pressed = true;
	
	TIMER0->ICR |= TIMER_ICR_TATOCINT;  //interrupt clear
}

/* since interrupt happens after x and y
 * we use joystick_int to signal which conversion
 * we have done
 */
void ADC0SS2_Handler() {
	uint32_t result;	
	
	//get the correct xy values
	if (joystick_int) {
		ps2_x = ADC0->SSFIFO2 & 0xFFF;		 // read 12-bit data
		joystick_int = false;
  } else {
		ps2_y = ADC0->SSFIFO2 & 0xFFF;		 // read 12-bit data
	  ADC0->ISC |= ADC_ISC_IN2;  		// Ack the conversion
		joystick_int = true;
	}
	//determine which, if any, direction is indicated on ps2
	if (ps2_y > ADC_MAX)
		ps2_up = true;
	if (ps2_y < ADC_MIN) 
		ps2_down = true;
	if (ps2_x > ADC_MAX)
		ps2_left = true;
	if (ps2_x < ADC_MIN)
		ps2_right = true;
}

//assumes there is a head, updates position of all obstacles, and redraws them
void update_obstacles() {
	struct obstacle_t *curr, *prev;
	curr = head;
	prev = NULL;
	
	//iterate through obstacles in linked list
	while (curr) {	
		curr->x_loc--;
		
		//draw obstacle or remove if its off screen
		if (curr->type == LEDGE && curr->x_loc <= LEDGE_WIDTH/2 - 1) {
			remove_obstacle(curr, prev);
		} 
		else {
			if(curr->type == WALL){
				//if pacman is unable to jump the wall, game over
				if((pacman.y_loc + PACMAN_HEIGHT/2) > (ROWS - (GND_HEIGHT + WALL_HEIGHT + 2)) && (pacman.x_loc + PACMAN_WIDTH/2 - 4) == (curr->x_loc - WALL_WIDTH/2 + 6)){
					game_over = true;
					break;
				}
				//increase the score if wall obstacle was tackled
				else if((pacman.y_loc + PACMAN_HEIGHT/2) <= (ROWS - (GND_HEIGHT + WALL_HEIGHT + 2)) && (pacman.x_loc + PACMAN_WIDTH/2 - 4) == (curr->x_loc - WALL_WIDTH/2 + 6)){
					score_baseline++;
					remove_obstacle(curr, prev);
				}
				else {
					lcd_draw_image(curr->x_loc, WALL_WIDTH, curr->y_loc, WALL_HEIGHT, wallBitMap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
				}
			}
			else if(curr->type == GHOST){
				//increase the score if ghost obstacle was tackled
				if((bullet.x_loc + BULLET_WIDTH/2) >= (curr->x_loc - GHOST_WIDTH/2) && bullet_button){
					score_baseline++;
					remove_obstacle(curr, prev);
				}
				//if pacman is unable to shoot the ghost, game over
				else if((pacman.x_loc + PACMAN_WIDTH/2) == (curr->x_loc - GHOST_WIDTH/2)){
					game_over = true;
					break;
				}
				else {
					lcd_draw_image(curr->x_loc, GHOST_WIDTH, curr->y_loc, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_RED, LCD_COLOR_BLACK);
				}
			}
			else if(curr->type == LEDGE){
				//if pacman is unable to duck under the ledge, game over
				if((pacman.x_loc + PACMAN_WIDTH/2 - 4) >= (curr->x_loc - LEDGE_WIDTH/2) && (pacman.x_loc + PACMAN_WIDTH/2 - 4) <= (curr->x_loc + LEDGE_WIDTH/2) && !ducking){
					game_over = true;
					break;
				}
				//increase the score if ledge obstacle was tackled
				if((pacman.x_loc + PACMAN_WIDTH/2 - 4) == (curr->x_loc - LEDGE_WIDTH/2) && ducking){
					score_baseline++;
				}
				lcd_draw_image(curr->x_loc, LEDGE_WIDTH, curr->y_loc, LEDGE_HEIGHT, ledgeBitMap, LCD_COLOR_GRAY, LCD_COLOR_BLACK);
			}
			else if(curr->type == FLAG){
				//inrease score if end of the game reached and flag crossed
				if((pacman.x_loc + PACMAN_WIDTH/2 - 4) == (curr->x_loc - FLAG_WIDTH/2)){
					score_baseline += 3; //bonus points
					game_winner = true;
					game_over = true;
					break;
				}
				lcd_draw_image(curr->x_loc, FLAG_WIDTH, curr->y_loc, FLAG_HEIGHT, flagBitMap, LCD_COLOR_RED, LCD_COLOR_BLACK);
			}
		}
		prev = curr;
		curr = curr->nxt;
	}
}

//erases obstacle from screen, and frees its memory
void remove_obstacle(struct obstacle_t * del_obstacle, struct obstacle_t * prev_obstacle) {
	//erase the obstacle (del_obstacle->x_loc + 1 b/c we decremented in the update)
	if(del_obstacle->type == WALL){
		lcd_draw_image(del_obstacle->x_loc + 1, WALL_WIDTH, del_obstacle->y_loc, WALL_HEIGHT, wallBitMap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	}
	else if(del_obstacle->type == GHOST){
		lcd_draw_image(del_obstacle->x_loc + 1, GHOST_WIDTH, del_obstacle->y_loc, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	}
	else if(del_obstacle->type == LEDGE){
		lcd_draw_image(del_obstacle->x_loc + 1, LEDGE_WIDTH, del_obstacle->y_loc, LEDGE_HEIGHT, ledgeBitMap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	}
	
	//remove obstacle from linked list and free memory
	if (!prev_obstacle) {  //this is the head
		head = head->nxt;
		free(del_obstacle);
	} else if (del_obstacle == tail) {	//this is the tail
	  prev_obstacle->nxt = NULL;
		tail = prev_obstacle;
		free(del_obstacle);
	}	else {  //this is somewhere in the middle of the list
		prev_obstacle->nxt = del_obstacle->nxt;
		free(del_obstacle);
	}
	
	//add obstacle if an obstacle is removed
	if (!end_flag)
		add_obstacle(0);
	else
		add_obstacle(1);
}

//add random obstacle or flag on completion at tail
void add_obstacle(uint8_t flag) {
	struct obstacle_t *curr;
	num_obstacles++;	
  
	//create new obstacle depending on flag
	curr = (struct obstacle_t *)malloc(sizeof(struct obstacle_t));
	if(flag == 0)
		curr->type = random_obstacle(); //randomize obstacles
	else 
		curr->type = FLAG;
	
	//set position of the appropriate obstacle
	if(curr->type == WALL){
		curr->x_loc = COLS + (WALL_WIDTH/2 + 1);
		curr->y_loc = GND_POS - (WALL_HEIGHT/2 + 1);
	}
	else if(curr->type == GHOST){
		curr->x_loc = COLS + (GHOST_WIDTH/2 + 1);
		curr->y_loc = GND_POS - (GHOST_HEIGHT/2 + 5);
	}
	else if(curr->type == LEDGE){
		curr->x_loc = COLS + (LEDGE_WIDTH/2 + 1);
		curr->y_loc = GND_POS - (LEDGE_HEIGHT/2 + 25);
	} 
	else if(curr->type == FLAG){
		curr->x_loc = COLS + (FLAG_WIDTH/2 + 1);
		curr->y_loc = GND_POS - (FLAG_HEIGHT/2 + 1);
	} 
	curr->nxt = NULL;
	
	//add at tail
	if (!head) { //list is empty
		head = curr;
		tail = curr;
	}	else {
		tail->nxt = curr;
		tail = curr;
	}
}

// randomize the obstacles
obstacle_type_t random_obstacle(){
	int num = rand() % 3;
	
	//select obstacle type based on num
	if(num == 0){
		return WALL;
	}
	else if(num == 1){
		return GHOST;
	}
	else {
		return LEDGE;
	}
}

//write high score to EEPROM
void write_high_score(high_score_t *score, uint16_t addr) {
	//write the letters first;
	eeprom_byte_write(I2C1_BASE, addr, (uint8_t)score->initials[0]);
	eeprom_byte_write(I2C1_BASE, addr+1, (uint8_t)score->initials[1]);
	eeprom_byte_write(I2C1_BASE, addr+2, (uint8_t)score->initials[2]);
	printf("addr of score.initials: %p\n", score->initials);
	//write the value next
	eeprom_byte_write(I2C1_BASE, addr+3, score->score);
	eeprom_byte_write(I2C1_BASE, addr+4, score->score >> 8);
}

//determines place finishing place if theres a new high score
//populates the high_score struct for use later
//displays the high scores for the end game screen
void print_high_scores() {
	char buffer[5];
	uint16_t eeprom_addr;
	uint16_t *curr_score;
	uint8_t i;
	uint8_t temp_score[2];
  eeprom_addr = ADDR_START;
	
	//read from eeprom to get the scores
	for (i = 0; i < 3; i++)
  {
		eeprom_byte_read(I2C1_BASE, eeprom_addr, (uint8_t*)&(scores[i].initials[0]));	
		eeprom_byte_read(I2C1_BASE, eeprom_addr + 1, (uint8_t*)&(scores[i].initials[1]));
		eeprom_byte_read(I2C1_BASE, eeprom_addr + 2, (uint8_t*)&(scores[i].initials[2]));
		eeprom_byte_read(I2C1_BASE, eeprom_addr + 3, (uint8_t*)&(temp_score[0]));
		eeprom_byte_read(I2C1_BASE, eeprom_addr + 4, (uint8_t*)&(temp_score[1]));
		scores[i].score = *((uint16_t*)&temp_score);
		printf("score %d initial: %c%c%c, score %d\n", i, scores[i].initials[0], scores[i].initials[1], scores[i].initials[2], scores[i].score);
		eeprom_addr += 5;
	}
	//display the high score names
	lcd_print_stringXY("HIGH SCORES", 4, 15, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	lcd_print_stringXY(scores[0].initials, 4, 16, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_print_stringXY(": ", 7, 16, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_print_stringXY(scores[1].initials, 4, 17, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_print_stringXY(": ", 7, 17, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_print_stringXY(scores[2].initials, 4, 18, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	lcd_print_stringXY(": ", 7, 18, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	
	//display the high score values
	curr_score = (uint16_t*)&scores[0];
	sprintf(buffer, "%d", scores[0].score);
	lcd_print_stringXY(buffer, 9, 16, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	sprintf(buffer, "%d", scores[1].score);
	lcd_print_stringXY(buffer, 9, 17, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	sprintf(buffer, "%d", scores[2].score);
	lcd_print_stringXY(buffer, 9, 18, LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
	
	//determine if theres a new high score
	if (scores[0].score < score)
		finishing_place = 1;
	else if (scores[1].score < score)
		finishing_place = 2;
	else if (scores[2].score < score)
		finishing_place = 3;
	else
		finishing_place = 0;
}
char *set_initials() {
	int8_t initial_index; //which char of the three you are on
	char *result;
	int8_t letter_indices[3];
	initial_index = letter_indices[0] = letter_indices[1] = letter_indices[2] = 0;
	result = malloc(4*sizeof(char));
	while (1) { //infinite loop while they put in initials
			if (initial_index == 0) {
					lcd_print_character(90, 200, LCD_COLOR_BLACK, LCD_COLOR_ORANGE, alphabet[letter_indices[0]]);
					lcd_print_character(110, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[1]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
				  lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
			} else if ( initial_index == 1) {
					lcd_print_character(90, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[0]]);
					lcd_print_character(110, 200, LCD_COLOR_BLACK, LCD_COLOR_ORANGE, alphabet[letter_indices[1]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[2]]);
			} else if (initial_index == 2) {
					lcd_print_character(90, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[0]]);
					lcd_print_character(110, 200, LCD_COLOR_ORANGE, LCD_COLOR_BLACK, alphabet[letter_indices[1]]);
					lcd_print_character(130, 200, LCD_COLOR_BLACK, LCD_COLOR_ORANGE, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_BLACK, LCD_COLOR_ORANGE, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_BLACK, LCD_COLOR_ORANGE, alphabet[letter_indices[2]]);
					lcd_print_character(130, 200, LCD_COLOR_BLACK, LCD_COLOR_ORANGE, alphabet[letter_indices[2]]);
  		}	
			//update letter selectors
			if (ps2_up) {
				if (letter_indices[initial_index] < 26) letter_indices[initial_index]++;
				ps2_y = 0x800;
				ps2_up = false;
			} else if (ps2_down) {
				if (letter_indices[initial_index] > 0) letter_indices[initial_index]--;
				ps2_y = 0x800;
				ps2_down = false;
			} else if (ps2_left) {
				initial_index ? initial_index-- : initial_index;
				ps2_x = 0x800;
				ps2_left = false;
			} else if (ps2_right) {
				initial_index != 2 ? initial_index++ : initial_index;
				ps2_x = 0x800;
				ps2_right = false;
			}
			//detect their save button
			if (sw1_pressed) {
				sw1_pressed = false;
				break;
			}
	}
	result[0] = alphabet[letter_indices[0]];
	result[1] = alphabet[letter_indices[1]];
	result[2] = alphabet[letter_indices[2]];
	result[3] = NULL;
	return result;
}


//Display the initial start screen
void start_game_screen() {
	//display welcome msg
	lcd_clear_screen(LCD_COLOR_BLACK);
	lcd_print_stringXY("Welcome to ", 1, 2, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
	lcd_print_stringXY("PacJump", 12, 2, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	lcd_print_stringXY("!", 19, 2, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);

	//display graphics:
	lcd_draw_image(60 , PACMAN_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	lcd_draw_image(63 + BULLET_WIDTH/2 + PACMAN_WIDTH/2, BULLET_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, BULLET_HEIGHT, bulletBitMap, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
	lcd_draw_image(126 + BULLET_WIDTH/2 + PACMAN_WIDTH/2 + GHOST_WIDTH/2, GHOST_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_RED, LCD_COLOR_BLACK);
	
	//display the ctrls for the game
	lcd_print_stringXY("Hold SW1 to start", 2, 14, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	lcd_print_stringXY("TWISTER: ", 2, 16, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	lcd_print_stringXY("Speed Ctrl", 11, 16, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	lcd_print_stringXY("RIGHT: ", 2, 17, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	lcd_print_stringXY("Flames", 11, 17, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
	lcd_print_stringXY("UP: ", 2, 18, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	lcd_print_stringXY("Jump", 11, 18, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	lcd_print_stringXY("DOWN: ", 2, 19, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	lcd_print_stringXY("Duck", 11, 19, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
}

//display the correct messages and initials input for the end of the game
void end_game_screen() {
	char buffer[5];
	char *initials;
	high_score_t new_high_score;
	
	//clear screen and display score, and the high scores
	lcd_clear_screen(LCD_COLOR_BLACK);
	lcd_print_stringXY("Score: ", 5, 4, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
	sprintf(buffer, "%d", score);
	lcd_print_stringXY(buffer, 12, 4, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
	print_high_scores(); //also determines your place
	
	//decide game result
	if (game_winner) {
		lcd_print_stringXY("YOU WIN!!", 6, 2, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	} else {
		lcd_print_stringXY("GAME OVER", 6, 2, LCD_COLOR_RED, LCD_COLOR_BLACK);
	}
	//determine if scores need to be update
	if (finishing_place) {
			printf("finishing_place: %d score global:%d\n", finishing_place, score);
			lcd_print_stringXY("NEW HIGH SCORE!!", 3, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			lcd_print_stringXY("Enter initials using joystick. Hold SW1  to save.", 1, 7, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			initials = set_initials();
			new_high_score.initials[0] = *initials;
			new_high_score.initials[1] = *(initials+1);
			new_high_score.initials[2] = *(initials+2);
			new_high_score.initials[3] = NULL;
			new_high_score.score = score;
			//move current high scores down if they were beaten
			if (finishing_place == 1) {
				write_high_score(&scores[1], ADDR_START + (2)*5);
				write_high_score(&scores[0], ADDR_START + (1)*5);
				write_high_score(&new_high_score, ADDR_START);
			} else if (finishing_place == 2) {
				write_high_score(&scores[1], ADDR_START + (2)*5);
				write_high_score(&new_high_score, ADDR_START + (1)*5);
			} else {
				write_high_score(&new_high_score, ADDR_START + (2)*5);
			}
			//reprint the new high scores
			print_high_scores();		
		} else {
			//multiple times to make it display the last letter correctly, hackish, but it was a weird issue
			lcd_print_stringXY("No broken records :(", 1, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			lcd_print_stringXY("No broken records :(", 1, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			lcd_print_stringXY("No broken records :(", 1, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			lcd_print_stringXY("No broken records :(", 1, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			lcd_print_stringXY("No broken records :(", 1, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
			lcd_print_stringXY("No broken records :(", 1, 6, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
		}
}

void redraw_pacman_jump(void) {
	static bool reached_height = false;
	static uint8_t count = 0;
	
	//redraw pacman going up 2 pixels at a time
	if(pacman.y_loc > ROWS - (GND_HEIGHT + WALL_HEIGHT + 26) && !reached_height) {
		pacman.y_loc--;
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
		pacman.y_loc--;
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	}
	//wait in the air
	else if (pacman.y_loc == ROWS - (GND_HEIGHT + WALL_HEIGHT + 26) && !reached_height && count < 15){
		count++;
	}
	//reset count once height reached
	else if (!reached_height){
		count = 0;
		reached_height = true;
	}
	//redraw pacman going up 2 pixels at a time
	else if	(pacman.y_loc < GND_POS - 26 && reached_height) {
		pacman.y_loc++;
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
		pacman.y_loc++;
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	}
	//reset flags
	else{
		reached_height = false;
		pacman.action = IDLE;
	}
}

void redraw_pacman_duck(void) {
	static bool duck_initial = true;
	
	//draw ducking pacman if down button pressed
	if(down_button && duck_initial){
		ducking = true;
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, GND_POS - 10, PACMAN_HEIGHT_DUCK, pacmanDuckBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
		duck_initial = false;
	}
	//reset flags
	else if (!down_button){
		//ongoing_action = false;
		ducking = false;
		duck_initial = true;
		pacman.action = IDLE;
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, GND_POS - 10, PACMAN_HEIGHT_DUCK, pacmanDuckBitMap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	}
}

void redraw_pacman_shooting(void){
	static bool bullet_initial = true;
	
	//draw fire if button is pressed down
	if(bullet_button && bullet_initial){
		bullet.x_loc = pacman.x_loc + PACMAN_WIDTH/2 + BULLET_WIDTH/2 - 5 ;
		bullet.y_loc = pacman.y_loc;
		lcd_draw_image(bullet.x_loc, BULLET_WIDTH, bullet.y_loc, BULLET_HEIGHT, bulletBitMap, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
		bullet_initial = false;
	}
	//reset flags
	else if (!bullet_button) {
		bullet_initial = true;
		ongoing_action = false;
		pacman.action = IDLE;
		lcd_draw_image(bullet.x_loc, BULLET_WIDTH, bullet.y_loc, BULLET_HEIGHT, bulletBitMap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	}
}

void redraw_all() {
	//call appropriate function based on flags
	if(pacman.action == IDLE && ongoing_action){
		lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
		ongoing_action = false;
	}
	else if(pacman.action == JUMP){
		redraw_pacman_jump();
	}
	else if(pacman.action == DUCK){
		redraw_pacman_duck();
	}
	else if(pacman.action == SHOOT){
		redraw_pacman_shooting();
	}
}

void update_score() {
	//calculate score using multiplier
	score = score_baseline * multiplier;
	sprintf(buffer_str, "%d", score);
	lcd_print_stringXY(buffer_str, 6, 0, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	
	//print multiplier value
	if (multiplier < 10) //clears the old double digit values
			lcd_print_stringXY(" ", 20, 0, LCD_COLOR_BLACK, LCD_COLOR_BLACK); 
	sprintf(buffer_str, "%d", multiplier);
	lcd_print_stringXY(buffer_str, 19, 0, LCD_COLOR_CYAN, LCD_COLOR_BLACK); 
}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	uint16_t count;
	uint8_t readval;
	uint32_t addr;
	high_score_t sample_score;

  initialize_hardware();
	
	/*
	//this is here if the high scores ever need to be cleared
	sample_score.initials[0] = '*';
	sample_score.initials[1] = '*';
	sample_score.initials[2] = '*';
	sample_score.score = 0;
	write_high_score(&sample_score, ADDR_START);
	sample_score.initials[0] = '*';
	sample_score.initials[1] = '*';
	sample_score.initials[2] = '*';
	sample_score.score = 0;
	write_high_score(&sample_score, ADDR_START + 5);
	sample_score.initials[0] = '*';
	sample_score.initials[1] = '*';
	sample_score.initials[2] = '*';
	sample_score.score = 0;
	write_high_score(&sample_score, ADDR_START + 10);*/
	
	// Initialize pacman location and image and state
	pacman.x_loc = 24; 
	pacman.y_loc = GND_POS - 26; //-10 to hover mid-air + -16 to center pacman
	pacman.action = IDLE;
	
	//show start game screen
	start_game_screen();
	lcd_print_stringXY("Multiplier: ", 3, 12, LCD_COLOR_BLUE, LCD_COLOR_BLACK); 
	
	//stay on the start screen until they push start button
	count = 0;
	while (!sw1_pressed) {
		//flash the ghost different colors
		if((count % 512) < 128)
			lcd_draw_image(126 + BULLET_WIDTH/2 + PACMAN_WIDTH/2 + GHOST_WIDTH/2, GHOST_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
		else if ((count%512) < 256)
			lcd_draw_image(126 + BULLET_WIDTH/2 + PACMAN_WIDTH/2 + GHOST_WIDTH/2, GHOST_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		else if ((count%512) < 384)
			lcd_draw_image(126 + BULLET_WIDTH/2 + PACMAN_WIDTH/2 + GHOST_WIDTH/2, GHOST_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
		else 
			lcd_draw_image(126 + BULLET_WIDTH/2 + PACMAN_WIDTH/2 + GHOST_WIDTH/2, GHOST_WIDTH, ROWS/2 - PACMAN_HEIGHT/2 - 15, GHOST_HEIGHT, ghostBitMap, LCD_COLOR_PINK, LCD_COLOR_BLACK);
		count++;
		
		//update the multiplier
		if((multiplier = get_qei1_pos()) == 0)
			multiplier = 1;
		
		//need to erase a digit if going from two digit multiplier to single digit
		if (multiplier < 10)
			lcd_print_stringXY(" ", 17, 12, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
		sprintf(buffer_str, "%d", multiplier);
		lcd_print_stringXY(buffer_str, 16, 12, LCD_COLOR_RED, LCD_COLOR_BLACK); 
	}
	
	//calculate speed based on multiplier
	speed -= multiplier*3/2;
	
	//clear screen
	lcd_clear_screen(LCD_COLOR_BLACK);
  
	// start the game by drawing pacman and ground
	lcd_draw_image(COLS/2, GND_WIDTH, GND_POS+35, GND_HEIGHT, groundBitMap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	lcd_draw_image(pacman.x_loc, PACMAN_WIDTH, pacman.y_loc, PACMAN_HEIGHT, pacmanBitMap, LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
	
	//print on screen the initial score and multiplier value
	lcd_print_stringXY("Score: ", 0, 0, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	lcd_print_stringXY("Mult: ", 13, 0, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	sprintf(buffer_str, "%d", multiplier);
	lcd_print_stringXY(buffer_str, 19, 0, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	score = score_baseline * multiplier;
	sprintf(buffer_str, "%d", score);
	lcd_print_stringXY(buffer_str, 6, 0, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
  
	srand(seed); //seed is determined by how long it takes them to start the game
	add_obstacle(0); //add the initial obstacle
	
	while(1){
		//update multiplier mid game
		if (read_qei) {
			if(get_qei1_pos() == 0)
				multiplier = 1;
			else
				multiplier = get_qei1_pos();
		
			speed = BASE_SPEED - multiplier*3/2;
			read_qei = false;
		}
		
		//sets back the switch button flag
		if (sw1_pressed) {
			sw1_pressed = false;
		}
		
		//draw pacman and all of the obstacles
		if(redraw){
			redraw = false;
			redraw_all();
			update_obstacles();
			update_score();
		}
		
		//start pacmans jump action
		if (up_button && !ongoing_action) {
			pacman.action = JUMP;
			ongoing_action = true;
			up_button = false;
		}

		//start pacmans duck action
		if (down_button && !ongoing_action) {
			pacman.action = DUCK;
			ongoing_action = true;
		}
		
		//start pacmans shooting action 
		if (bullet_button && !ongoing_action) {
			pacman.action = SHOOT;
			ongoing_action = true;
		}
		
		//determine when the flag is reached
		if(num_obstacles == 20){
			end_flag = true;
		}
		
		//game is over, so you should go to the end screen
		if (game_over) {
			break; //leave the loop that plays the game.
		}
	}
	end_game_screen();
}
