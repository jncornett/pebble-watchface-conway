//
//  game.h
//  
//
//  Created by Joel Cornett on 10/17/13.
//
//

#ifndef _game_h
#define _game_h

#include "pebble_os.h"

#define BOARD_SIZE_X    12
#define BOARD_SIZE_Y    12

typedef struct RULE_STRUCT Rule_t;

void game_init(uint8_t rule, uint8_t density);
void game_step(void);
uint8_t get_value(uint8_t x, uint8_t y);

#endif
