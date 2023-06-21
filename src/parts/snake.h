/* H file of snake functions */
#ifndef SNAKE_GAME_SNAKE_H
#define SANKE_GAME_SNAKE_H

#include "background.h"

#define SNAKE_MOVE_UP -1
#define SNAKE_MOVE_DOWN 1
#define SNAKE_MOVE_LEFT -1
#define SNAKE_MOVE_RIGHT 1

typedef struct part_s {
        Point location; // record the location of the snake part
        struct part_s *prev;
        struct part_s *next;
} Snake_part;

Snake_part *snake_init(Background *bg);
bool snake_move(Snake_part *snake_head, Background *bg, int direc);
void snake_destroy(Snake_part *snake_head);

#endif
