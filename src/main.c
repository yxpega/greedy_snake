/* Implement main game interactive part */
#include <string.h>
#include <stdio.h>
#include "snake.h"

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

int main(void)
{
        Background bg;
        memset(&bg, 0, sizeof(Background));

        generate_bg(&bg);
        print_bg(bg.bg_path);
        return 0;
}