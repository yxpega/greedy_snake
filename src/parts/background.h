/* H file of greedy snake game background */

#ifndef SNAKE_GAME_BG_H
#define SNAKE_GAME_BG_H
#include <stdbool.h>

#define BG_BOUNDER 20

enum bg_type {
        bg_empty = 0,   // use " " to denote empty
        bg_wall,        // use "#" to denote wall
        bg_food,        // use "+" to denote food
        bg_snake_head,  // use "o" to denote snake head
        bg_snake_body,  // use "*" to denote snake body
};

typedef struct point_s {
        int x;
        int y;
} Point;

typedef struct bg_s {
        int wall_num;
        int food_num;
        enum bg_type bg_path[BG_BOUNDER][BG_BOUNDER];
} Background;

void generate_bg(Background *bg);
bool is_point_valid(Background *bg, Point p);
bool is_point_food(Background *bg, Point p);

#endif
