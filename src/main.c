/* Implement main game interactive part */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "snake.h"

#define INPUTKEY_SIZE 32
#define INPUTKEY_UP 355
#define INPUTKEY_DOWN 356
#define INPUTKEY_LEFT 358
#define INPUTKEY_RIGHT 357
#define INPUTKEY_ESC 27
#define INPUTKEY_SPACE 32
#define INPUTKEY_ONE 49
#define INPUTKEY_TWO 50

int getch(void)
{
        int key_val = 0;
        char buf[INPUTKEY_SIZE] = {0};
        struct termios old = {0};

        fflush(stdout);
        if (tcgetattr(0, &old) < 0) {
                perror("tcsetattr error!\n");
        }

        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;

        if (tcsetattr(0, TCSANOW, &old) < 0) {
                perror("tcsetattr ICANON error!");
        }

        if (read(0, &buf, INPUTKEY_SIZE) < 0) {
                perror("read() error!");
        }

        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;

        if (tcsetattr(0, TCSADRAIN, &old) < 0) {
                perror("tcsetattr ~ICANON error!");
        }

        for (int i = 0; i < strlen(buf); i++) {
                key_val = (key_val << 1) + (int)buf[i];
        }
        return key_val;
}

static void game_instruction(void)
{
        printf("======================================================================\n");
        printf("Welcome to the world of greedy snake!\n\n");
        printf("1. Use UP, DOWN, LEFT, RIGHT key to move snake.\n");
        printf("2. \"+\" is food that can make your snake grow up.\n");
        printf("3. \"#\" is wall that can destroy your snake.\n");
        printf("4. From level 2, you can change your snake mode at the beginning of each level.\n");
        printf("5. In offensive mode, you can use \"space\" key to destroy wall.\n");
        printf("   But be careful of your snake body, don't hit it!\n");
        printf("6. If you want to quit the game, press ESC key.\n");
        printf("======================================================================\n");
        printf("\nPress any key to conitnue...\n");
        getch();
}

static void goto_next_level(Background *bg, Snake_part *snake)
{
        levelup_bg(bg);
        snake_putto_background(bg, snake);
        generate_bg(bg);
        snake_load_bullets(bg, snake);

        system("clear");
        print_bg(bg);
        printf("At the beginning of level %u, you can choose the following mode:\n",
               bg->level);
        printf("penetrable_mode: press 1...\n");
        printf("offensive_mode: press 2...\n");

        int key = getch();
        switch(key) {
                case INPUTKEY_ONE:
                        snake_set_mode(snake, penetrable_mode);
                        printf("set penetrable_mode success...\n");
                        break;
                case INPUTKEY_TWO:
                        snake_set_mode(snake, offensive_mode);
                        printf("Set offensive_mode success...\n");
                        break;
                default:
                        printf("key error: continue to use the last mode...\n");
                        break;
        }
}

int main(void)
{
        game_instruction();

        Background bg = {0};

        Snake_part *snake = snake_init(&bg);
        snake_putto_background(&bg, snake);
        generate_bg(&bg);

        int input_key = 0;
        bool move_ok = true;
        bool running = true;
        system("clear");
        print_bg(&bg);
        while (true) {
                input_key = getch();
                switch ((int)input_key) {
                        case INPUTKEY_UP:
                                move_ok = snake_move_onbg_ok(&bg, snake, SNAKE_MOVE_UP);
                                break;
                        case INPUTKEY_DOWN:
                                move_ok = snake_move_onbg_ok(&bg, snake, SNAKE_MOVE_DOWN);
                                break;
                        case INPUTKEY_LEFT:
                                move_ok = snake_move_onbg_ok(&bg, snake, SNAKE_MOVE_LEFT);
                                break;
                        case INPUTKEY_RIGHT:
                                move_ok = snake_move_onbg_ok(&bg, snake, SNAKE_MOVE_RIGHT);
                                break;
                        case INPUTKEY_ESC:
                                running = false;
                                break;
                        case INPUTKEY_SPACE:
                                snake_shoot_bullets(&bg, snake);
                                break;
                        default:
                                break;
                }

                system("clear");
                print_bg(&bg);

                if (!running) {
                        printf("Goodbye Little Snake~...\n");
                        break;
                }

                if (!move_ok) {
                        printf("Ooops! You failed level %d... T~T\n",
                               bg.level);
                        break;
                }

                if (snake->mode == penetrable_mode) {
                        printf("snake_mode: penetrable_mode\n");
                } else {
                        printf("snake_mode: offensive_mode\n");
                        printf("bullets: %u\n", snake->bullets);
                }

                if (bg.food_num == 0) {
                        printf("Wow! Snake is full now... ^_<\n");
                        if (bg.level == BG_MAX_LEVEL) {
                                printf("You win! You have finally achieved level %u!\n",
                                       bg.level);
                                printf("You are an excellent snake feeder! O(n_n)O\n");
                                break;
                        } else {
                                printf("Congratulations! Level up to %u!\n",
                                       bg.level + 1);
                                printf("Press any key to continue...\n");
                                getch();
                                goto_next_level(&bg, snake);
                       }
                }
        }

        snake_destroy(snake);

        return 0;
}
