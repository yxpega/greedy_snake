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
        printf("%d\n", key_val);
        return key_val;
}

int main(void)
{
        Background bg;
        memset(&bg, 0, sizeof(Background));
        generate_bg(&bg);

        Snake_part *snake = snake_init(&bg);
        snake_putto_background(&bg, snake);

        int input_key;
        while (1) {
                input_key = getch();
                printf("...\n");
                switch ((int)input_key) {
                        case INPUTKEY_UP:
                                printf("UP\n");
                                break;
                        case INPUTKEY_DOWN:
                                printf("DOWN\n");
                                break;
                        case INPUTKEY_LEFT:
                                printf("LEFT\n");
                                break;
                        case INPUTKEY_RIGHT:
                                printf("RIGHT\n");
                                break;
                        case INPUTKEY_ESC:
                                printf("ESC\n");
                                break;
                        default:
                                break;
                }
        }

        snake_destroy(snake);

        return 0;
}
