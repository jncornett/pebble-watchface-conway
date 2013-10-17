//
//  game.c
//  
//
//  Created by Joel Cornett on 10/17/13.
//
//

/* Includes */
#include "game.h"

/* Structures */
struct RULE_STRUCT {
    uint8_t rules[5];
    uint8_t compressed;
};

/* Static Variables */
uint8_t _back_idx;
uint8_t _buffers[2][BOARD_SIZE_X][BOARD_SIZE_Y];
uint8_t _density;
Rule_t _rule;

/* Static Headers */
static void expand_rule(uint8_t rule, Rule_t *p_rule);
static inline uint8_t rand_from_density(uint8_t density);
static inline uint8_t toggle(uint8_t value);
static uint8_t get_num_neighbors(uint8_t x, uint8_t y);

/* Public Implementations */
void game_init(uint8_t rule, uint8_t density) {
    uint8_t i, j;
    srand(time(NULL));
    
    _density = density;
    _back_idx = 1;
    
    //Populate front and back buffers
    for (i = 0; i < BOARD_SIZE_X; i++) {
        for (j = 0; j < BOARD_SIZE_Y; j++) {
            _buffers[0][i][j] = rand_from_density(density);
        }
    }
    
    expand_rule(rule, &_rule);
}

void game_step(void) {
    uint8_t i, j, cur, r, changes = 0;
    
    for (i = 0; i < BOARD_SIZE_X; i++) {
        for (j = 0; j < BOARD_SIZE_Y; j++) {
            r = _rule.rules[get_num_neighbors(i, j)];
            cur = _buffers[_back_idx][i][j];
            if (r != cur) {
                _buffers[_back_idx][i][j] = r;
                changes = 1;
            }
        }
    }
    
    _back_idx = toggle(_back_idx);
    
    if (changes == 0) {
        game_init(_rule.compressed, _density);
    }
}

uint8_t get_value(uint8_t x, uint8_t y) {
    return _buffers[toggle(_back_idx)][x][y];
}

/* Static Implementations */
static void expand_rule(uint8_t rule, Rule_t *p_rule) {
    uint8_t i;
    
    for (i = 0; i < 5; i++) {
        if ((rule & 0x01U) != 0) p_rule->rules[i] = 1;
        else p_rule->rules[i] = 0;
        rule >>= 1;
    }
    
    p_rule->compressed = rule;
}

static inline uint8_t rand_from_density(uint8_t density) {
    return ((rand() % 100) < density)? 1: 0;
}

static inline uint8_t toggle(uint8_t value) {
    return (value == 1)? 0: 1;
}

static uint8_t get_num_neighbors(uint8_t x, uint8_t y) {
    uint8_t total = 0;
    uint8_t (*cur_buffer)[BOARD_SIZE_X][BOARD_SIZE_Y] = &_buffers[toggle(_back_idx)];
    
    if ((*cur_buffer)[(x + 1) % BOARD_SIZE_X][y] == 1) total++;
    if ((*cur_buffer)[(x - 1) % BOARD_SIZE_X][y] == 1) total++;
    if ((*cur_buffer)[x][(y + 1) % BOARD_SIZE_Y] == 1) total++;
    if ((*cur_buffer)[x][(y - 1) % BOARD_SIZE_Y] == 1) total++;
    
    return total;
}

