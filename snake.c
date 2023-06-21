/* Implement snake functions */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "snake.h"

Snake_part *snake_init(Background *bg)
{
        Point init_loc;
        Snake_part *snake_head = malloc(sizeof(Snake_part));
        assert(snake_head != NULL);
        memset(snake_head, 0, sizeof(Snake_part));

        snake_head->prev = snake_head;
        snake_head->next = snake_head;

        do {
                init_loc.x = rand() % BG_BOUNDER;
                init_loc.y = rand() % BG_BOUNDER;
        } while (!is_point_valid(bg, init_loc));
        snake_head->location = init_loc;

        return snake_head;
}

static void __snake_add_tail(Snake_part *snake_head, Point location)
{
        assert(snake_head != NULL);
        Snake_part *new_part = malloc(sizeof(Snake_part));
        assert(new_part != NULL);

        new_part->location = location;
        new_part->prev = snake_head->prev;
        new_part->next = snake_head;
        snake_head->prev = new_part;
        new_part->prev->next = new_part;
}

static void __snake_add_tohead(Snake_part *snake_head, Point location)
{
        assert(snake_head != NULL);
        Snake_part *new_part = malloc(sizeof(Snake_part));
        assert(new_part != NULL);

        new_part->location = location;
        new_part->next = snake_head->next;
        new_part->prev = snake_head;
        snake_head->next = new_part;
        new_part->next->prev = new_part;
}

static bool __snake_part_isempty(Snake_part *snake_head)
{
        return snake_head->next == snake_head;
}

static Point __snake_pop_tail(Snake_part *snake_head)
{
        assert(snake_head != NULL);
        assert(!__snake_part_isempty(snake_head));

        Point tail_loc;

        Snake_part *drop_n = snake_head->prev;
        snake_head->prev = drop_n->prev;
        drop_n->prev->next = snake_head;
        drop_n->next = NULL;
        drop_n->prev = NULL;

        tail_loc = drop_n->location;
        free(drop_n);

        return tail_loc;
}

bool snake_move(Snake_part *snake_head, Background *bg, int direc)
{
        assert(snake_head != NULL);
        Point prev_head_loc = snake_head->location;

        if (direc == SNAKE_MOVE_UP || direc == SNAKE_MOVE_DOWN) {
                snake_head->location.y += direc;
        } else {
                snake_head->location.x += direc;
        }

        if (!is_point_valid(bg, snake_head->location)) {
                return false;
        }
        if (!is_point_food(bg, snake_head->location)) {
                __snake_pop_tail(snake_head);
        }
        __snake_add_tohead(snake_head, prev_head_loc);

        return true;
}

void snake_destroy(Snake_part *snake_head)
{
        assert(snake_head != NULL);
        while (!__snake_part_isempty(snake_head)) {
                __snake_pop_tail(snake_head);
        }
        free(snake_head);
}
