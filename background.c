/* Implement greedy snake backgroud */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "background.h"

void print_bg(enum bg_type (*background)[BG_BOUNDER])
{
        for (int i = 0; i < BG_BOUNDER + 2; i++) {
                printf("#");
        }
        printf("\n");

        for (int r = 0; r < BG_BOUNDER; r++) {
                printf("#");
                for (int c = 0; c < BG_BOUNDER; c++) {
                        switch (background[r][c]) {
                                case bg_wall:
                                        printf("#");
                                        break;
                                case bg_food:
                                        printf("+");
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
}

static void set_bg(Background *bg, int num, enum bg_type type)
{
        for (int i = 0; i < num; i++) {
                Point tmp_p;
                do {
                        tmp_p.x = rand() % BG_BOUNDER;
                        tmp_p.y = rand() % BG_BOUNDER;
                } while (bg->bg_path[tmp_p.x][tmp_p.y] == type);
                bg->bg_path[tmp_p.x][tmp_p.y] = type;
        }
}

void generate_bg(Background *bg)
{
        bg->wall_num = rand() % (BG_BOUNDER * BG_BOUNDER / 10);
        bg->food_num = rand() % (BG_BOUNDER * BG_BOUNDER / 10);

        set_bg(bg, bg->wall_num, bg_wall);
        set_bg(bg, bg->food_num, bg_food);
}

bool is_point_valid(Background *bg, Point p)
{
        return p.x >= 0 && p.x < BG_BOUNDER &&
               p.y >= 0 && p.y < BG_BOUNDER &&
               bg->bg_path[p.x][p.y] != bg_wall;
}

bool is_point_food(Background *bg, Point p)
{
        return is_point_valid(bg, p) && bg->bg_path[p.x][p.y] == bg_food;
}

int main()
{
        Background bg;
        memset(&bg, 0, sizeof(Background));

        generate_bg(&bg);
        print_bg(bg.bg_path);
        return 0;
}
