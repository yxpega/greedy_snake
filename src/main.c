/* Implement main game interactive part */
#include <string.h>
#include <stdio.h>
#include "snake.h"

int main(void)
{
        Background bg;
        memset(&bg, 0, sizeof(Background));
        generate_bg(&bg);

        Snake_part *snake = snake_init(&bg);
        snake_putto_background(&bg, snake);

        print_bg(&bg);
        snake_destroy(snake);
        return 0;
}
