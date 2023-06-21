/* Implement greedy snake backgroud */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "background.h"

static void __set_bg(Background *bg, unsigned int num, enum bg_type type)
{
        for (unsigned int i = 0u; i < num; i++) {
                Point tmp_p;
                do {
                        tmp_p.x = rand() % BG_BOUNDER;
                        tmp_p.y = rand() % BG_BOUNDER;
                } while (bg->bg_path[tmp_p.x][tmp_p.y] != bg_empty);
                bg->bg_path[tmp_p.x][tmp_p.y] = type;
        }
}

void levelup_bg(Background *bg)
{
        bg->level++;
        bg->food_num = 0u;
        bg->wall_num = 0u;
        memset(bg->bg_path, 0, sizeof(bg->bg_path));
}

void generate_bg(Background *bg)
{
        if (bg->level == 0u) {
                bg->level++;
        }

        bg->wall_num = (bg->level - 1) * 2;
        bg->food_num = bg->level;

        __set_bg(bg, bg->wall_num, bg_wall);
        __set_bg(bg, bg->food_num, bg_food);
}

void print_bg(Background *bg)
{
        for (int i = 0; i < BG_BOUNDER + 2; i++) {
                printf("#");
        }
        printf("\n");

        for (int r = 0; r < BG_BOUNDER; r++) {
                printf("#");
                for (int c = 0; c < BG_BOUNDER; c++) {
                        switch (bg->bg_path[r][c]) {
                                case bg_wall:
                                        printf("#");
                                        break;
                                case bg_food:
                                        printf("+");
                                        break;
                                case bg_snake_head:
                                        printf("o");
                                        break;
                                case bg_snake_body:
                                        printf("*");
                                        break;
                                case bg_snake_bullet:
                                        printf("-");
                                        break;
                                default:
                                        printf(" ");
                                        break;
                        }
                }
                printf("#\n");
        }

        for (int i = 0; i < BG_BOUNDER + 2; i++) {
                printf("#");
        }
        printf("\n");
        printf("level: %u\n", bg->level);
}

bool is_point_inbg(Background *bg, Point p)
{
        return p.x >= 0 && p.x < BG_BOUNDER &&
               p.y >= 0 && p.y < BG_BOUNDER;
}

bool is_point_valid(Background *bg, Point p)
{
        return is_point_inbg(bg, p) &&
               bg->bg_path[p.x][p.y] != bg_wall;
}

bool is_point_food(Background *bg, Point p)
{
        return is_point_valid(bg, p) && bg->bg_path[p.x][p.y] == bg_food;
}
