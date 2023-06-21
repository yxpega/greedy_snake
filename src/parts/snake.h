/* H file of snake functions */
#ifndef SNAKE_GAME_SNAKE_H
#define SANKE_GAME_SNAKE_H

#include "background.h"

#define SNAKE_MOVE_UP 0u
#define SNAKE_MOVE_DOWN 1u
#define SNAKE_MOVE_LEFT 2u
#define SNAKE_MOVE_RIGHT 3u
#define SNAKE_MOVE_INVAL 4u

enum snake_mode {
        /* default mode: snake is allowed to hit its body and penetrate the body */
        penetrable_mode = 0u,
        /* snake will die if hits its body,
         * but it can shoot bullets to destroy the background wall */
        offensive_mode = 1u,
};

typedef struct part_s {
        enum snake_mode mode;
        unsigned int bullets;
        unsigned int prev_direc; // moving direction of last step, default is move_up
        Point location; // record the location of the snake part
        struct part_s *prev;
        struct part_s *next;
} Snake_part;

void snake_load_bullets(Background *bg, Snake_part *snake);
void snake_shoot_bullets(Background *bg, Snake_part *snake);
void snake_exchange_mode(Snake_part *snake);
Snake_part *snake_init(Background *bg);
void snake_putto_background(Background *bg, Snake_part *snake);
bool snake_move_onbg_ok(Background *bg, Snake_part *snake_head, unsigned int direc_type);
void snake_destroy(Snake_part *snake_head);

#endif
