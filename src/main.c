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

int main(void)
{
        Background bg = {0};

        Snake_part *snake = snake_init(&bg);
        snake_putto_background(&bg, snake);
        generate_bg(&bg);

        int input_key = 0;
        bool move_ok = true;
        bool running = true;
        system("clear");
        print_bg(&bg);
        while (running) {
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
                                printf("Goodbye Little Snake~...\n");
                                break;
                        default:
                                break;
                }

                if (!move_ok) {
                        printf("Ooops! You failed level %d... T~T\n",
                               bg.level);
                        break;
                }

                system("clear");
                print_bg(&bg);

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

                                levelup_bg(&bg);
                                snake_putto_background(&bg, snake);
                                generate_bg(&bg);
                                getch();
                                system("clear");
                                print_bg(&bg);
                        }
                }
        }

        snake_destroy(snake);

        return 0;
}
