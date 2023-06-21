/* Implement snake functions */
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "snake.h"

static const Point direct[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void snake_load_bullets(Background *bg, Snake_part *snake)
{
        assert(bg != NULL);
        assert(snake != NULL);

        snake->bullets = bg->wall_num / 2;
}

void snake_shoot_bullets(Background *bg, Snake_part *snake)
{
        if (snake->mode != offensive_mode || snake->bullets == 0u) {
                return;
        }

        snake->bullets--;

        Point cur = snake->location;
        Point mov = direct[snake->prev_direc];
        cur.x += mov.x;
        cur.y += mov.y;

        while (is_point_inbg(bg, cur)) {
                system("clear");
                enum bg_type prev_bg = bg->bg_path[cur.x][cur.y];
                bg->bg_path[cur.x][cur.y] = bg_snake_bullet;
                print_bg(bg);
                bg->bg_path[cur.x][cur.y] = prev_bg;

                if (bg->bg_path[cur.x][cur.y] == bg_wall) {
                        bg->bg_path[cur.x][cur.y] = bg_empty;
                        system("clear");
                        print_bg(bg);
                        break;
                }
                cur.x += mov.x;
                cur.y += mov.y;

                /* To slow down the bullets speed to make eye detectable */
                usleep(20000);
        }
}

void snake_exchange_mode(Snake_part *snake)
{
        assert(snake != NULL);
        snake->mode = 1u - snake->mode;
}

Snake_part *snake_init(Background *bg)
{
        Point init_loc;
        Snake_part *snake_head = malloc(sizeof(Snake_part));
        assert(snake_head != NULL);
        memset(snake_head, 0, sizeof(Snake_part));

        snake_head->prev = snake_head;
        snake_head->next = snake_head;

        init_loc.x = rand() % BG_BOUNDER;
        init_loc.y = rand() % BG_BOUNDER;
        snake_head->location = init_loc;

        return snake_head;
}

void snake_putto_background(Background *bg, Snake_part *snake)
{
        assert(bg != NULL);
        assert(snake != NULL);

        Point loc;
        Snake_part *cur_part = snake;
        do {
                loc = cur_part->location;
                bg->bg_path[loc.x][loc.y] = bg_snake_body;
                cur_part = cur_part->next;
        } while (cur_part != snake);

        /* draw head at last */
        loc = snake->location;
        bg->bg_path[loc.x][loc.y] = bg_snake_head;
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

bool __snake_is_hitself(Background *bg, Snake_part *snake_head)
{
        assert(bg != NULL);
        assert(snake_head != NULL);

        Point loc = snake_head->location;
        Point tail = snake_head->prev->location;
        return (tail.x != loc.x || tail.y != loc.y) &&
               (bg->bg_path[loc.x][loc.y] == bg_snake_body ||
               bg->bg_path[loc.x][loc.y] == bg_snake_head);
}

bool snake_move_onbg_ok(Background *bg,
                        Snake_part *snake_head,
                        unsigned int direc_type)
{
        assert(snake_head != NULL);
        Point mov_loc;
        Point prev_head_loc = snake_head->location;

        if (direc_type >= SNAKE_MOVE_INVAL) {
                /* other direc will just pass this movement */
                return true;
        } else {
                snake_head->location.x += direct[direc_type].x;
                snake_head->location.y += direct[direc_type].y;
                snake_head->prev_direc = direc_type;
        }

        if (!is_point_valid(bg, snake_head->location) ||
            (snake_head->mode == offensive_mode &&
             __snake_is_hitself(bg, snake_head))) {
                bg->bg_path[prev_head_loc.x][prev_head_loc.y] = bg_snake_g;
                return false;
        }

        /* add body to prev head location */
        __snake_add_tohead(snake_head, prev_head_loc);

        /* if not food point, remove tail */
        if (!is_point_food(bg, snake_head->location)) {
                mov_loc = __snake_pop_tail(snake_head);
                bg->bg_path[mov_loc.x][mov_loc.y] = bg_empty;
        } else {
                bg->food_num--;
        }

        /* put current snake to background */
        snake_putto_background(bg, snake_head);
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
