#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

#include "structs.h"
#include "macros.h"
#include "utils.h"

extern Config config;
Map map;

void drawBoarder() {
    // clearScreen();
    gotoxy(0, 0);
    printf(LEFT_CORNER);
    for (int x = 0; x < config.map_width; x++) {
        printf(TOP_BOTTOM_WALL);
    }
    printf(RIGHT_CORNER);

    for (int y = 0; y <config.map_height; y++) {
        gotoxy(0, y + 1);
        printf(LEFT_WALL);
        gotoxy(config.map_width * 2 + 2, y + 1);
        printf(RIGHT_WALL);
    }

    gotoxy(0, config.map_height + 1);
    printf(LEFT_CORNER);
    for (int x = 0; x < config.map_width; x++) {
        printf(TOP_BOTTOM_WALL);
    }
    printf(RIGHT_CORNER);
}

void initGame(Snake *snake, Point *food) {
    // drawBoarder();
    snake->length = 1;
    snake->body[0].x = config.map_width / 2;
    snake->body[0].y = config.map_height / 2;
    snake->direction = RIGHT;

    food->x = rand() % config.map_width;
    food->y = rand() % config.map_height;
}
void drawBoard(Snake *snake, Point *food) {
    // clearScreen();
    drawBoarder();
    for (int y = 0; y < config.map_height; y++) {
        for (int x = 0; x < config.map_width; x++) {
            gotoxy(x * 2 + 2, y + 1);
            int isBody = 0;
            for (int k = 0; k < snake->length; k++) {
                if (snake->body[k].x == x && snake->body[k].y == y) {
                    isBody = 1;
                    break;
                }
            }
            if (isBody) {
                printf(SNAKE_BODY);
            } else if (food->x == x && food->y == y) {
                printf(FOOD);
            } else {
                printf(EMPTY);
            }
        }
        printf("\n");
    }
}

void moveSnake(Snake *snake) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->direction) {
        case UP:
            snake->body[0].y--;
            break;
        case DOWN:
            snake->body[0].y++;
            break;
        case LEFT:
            snake->body[0].x--;
            break;
        case RIGHT:
            snake->body[0].x++;
            break;
    }

    if (snake->body[0].x >= config.map_width) snake->body[0].x = 0;
    if (snake->body[0].x < 0) snake->body[0].x = config.map_width - 1;
    if (snake->body[0].y >= config.map_height) snake->body[0].y = 0;
    if (snake->body[0].y < 0) snake->body[0].y = config.map_height - 1;
}

int checkCollision(Snake *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}

void updateDirection(Snake *snake) {
    int ch = getch();
    switch (ch) {
        case 'w':
            if (snake->direction != DOWN) snake->direction = UP;
            break;
        case 's':
            if (snake->direction != UP) snake->direction = DOWN;
            break;
        case 'a':
            if (snake->direction != RIGHT) snake->direction = LEFT;
            break;
        case 'd':
            if (snake->direction != LEFT) snake->direction = RIGHT;
            break;
    }
}

int errorFood(Snake *snake,Point *food) {
    for (int i = 1; i < snake->length; i++) {
        if (food->x == snake->body[i].x && food->y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}

int eatFood(Snake *snake, Point *food) {
    if (snake->body[0].x == food->x && snake->body[0].y == food->y) {
        snake->length++;
        food->x = rand() % config.map_width;
        food->y = rand() % config.map_height;
        // BUG: food refresh in the snake body
        while(errorFood(snake,food)){
            food->x = rand() % config.map_width;
            food->y = rand() % config.map_height;
        }
        return 1;
    }
    return 0;
}