# Greedy Snake Game
Here is an implementation of a traditional game of greedy snake.

### Getting stuff ready to roll
1. clone this repo

   ```shell
   git clone https://github.com/yxpega/greedy_snake.git
   ```

2. compile the project

   ```shell
   cd greedy_snake
   mkdir build
   cd build
   cmake ../src/
   make
   ```

3. run the game

   ```shell
   ./greedy_snake
   ```

### Game instructions

1. There are different levels in the game. You can level up when your snake eats all the food.
2. Use keyboard **UP**, **DOWN**, **LEFT**, **RIGHT** to move your snake.
3. "+" is the food that can help your snake grow up.
4. "#" is the wall that can hurt your little snake. Be careful of it!
5. After level 2, you may have two mode to choose:
   - penetrable mode (default): your snake can penetrate its body. (press 1)
   - offensive mode: your snake is sensitive to hit its body, but it can shoot bullets (press ESC) to destroy the wall. (press 2)
6. You win when you pass all the levels.
7. Press **ESC** to quit the game whenever you want.

### Game show

```shell
======================================================================
Welcome to the world of greedy snake!

1. Use UP, DOWN, LEFT, RIGHT key to move snake.
2. "+" is food that can make your snake grow up.
3. "#" is wall that can destroy your snake.
4. From level 2, you can change your snake mode at the beginning of each level.;
5. In offensive mode, you can use "space" key to destroy wall.
   But be careful of your snake body, don't hit it!
6. If you want to quit the game, press ESC key.
======================================================================

Press any key to conitnue...
```

```shell
######################
#                    #
#                    #
#          #         #
#                    #
#       +       +    #
#     #              #
#         +  o       #
#   **********       #
#                    #
#                    #
#                    #
##                   #
#                    #
#      #          +  #
#                    #
#          #         #
# #   +       #      #
#                    #
#    #               #
#                    #
######################
snake_mode: penetrable_mode
```
