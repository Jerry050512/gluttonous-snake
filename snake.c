#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "macros.h"
#include "utils.h"

void initGame(Snake *snake, Point *food) {
    snake->length = 1;
    snake->body[0].x = WIDTH / 2;
    snake->body[0].y = HEIGHT / 2;
    snake->direction = RIGHT;

    food->x = rand() % WIDTH;
    food->y = rand() % HEIGHT;
}

void drawBoard(Snake *snake, Point *food) {
    clearScreen();
    gotoxy(0, 0);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int isBody = 0;
            for (int k = 0; k < snake->length; k++) {
                if (snake->body[k].x == x && snake->body[k].y == y) {
                    isBody = 1;
                    break;
                }
            }
            if (isBody) {
                printf("O");
            } else if (food->x == x && food->y == y) {
                printf("*");
            } else {
                printf("-");
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

    if (snake->body[0].x >= WIDTH) snake->body[0].x = 0;
    if (snake->body[0].x < 0) snake->body[0].x = WIDTH - 1;
    if (snake->body[0].y >= HEIGHT) snake->body[0].y = 0;
    if (snake->body[0].y < 0) snake->body[0].y = HEIGHT - 1;
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
    int ch = getchar();
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

int eatFood(Snake *snake, Point *food) {
    if (snake->body[0].x == food->x && snake->body[0].y == food->y) {
        snake->length++;
        food->x = rand() % WIDTH;
        food->y = rand() % HEIGHT;
        return 1;
    }
    return 0;
}