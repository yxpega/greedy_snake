/* H file of snake functions */
#ifndef SNAKE_GAME_SNAKE_H
#define SANKE_GAME_SNAKE_H

#include "background.h"

#define SNAKE_MOVE_UP 0u
#define SNAKE_MOVE_DOWN 1u
#define SNAKE_MOVE_LEFT 2u
#define SNAKE_MOVE_RIGHT 3u
#define SNAKE_MOVE_INVAL 4u

typedef struct part_s {
        Point location; // record the location of the snake part
        struct part_s *prev;
        struct part_s *next;
} Snake_part;

Snake_part *snake_init(Background *bg);
void snake_putto_background(Background *bg, Snake_part *snake);
bool snake_move_onbg_ok(Background *bg, Snake_part *snake_head, unsigned int direc_type);
void snake_destroy(Snake_part *snake_head);

#endif
