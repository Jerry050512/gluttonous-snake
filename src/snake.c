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

void drawBoarder(Map *map)
{
    // clearScreen();
    gotoxy(0, 0);
    printf(LEFT_CORNER);
    for (int x = 0; x < map->width; x++) {
        printf(TOP_BOTTOM_WALL);
    }
    printf(RIGHT_CORNER);

    for (int y = 0; y <map->height; y++) {
        gotoxy(0, y + 1);
        printf(LEFT_WALL);
        gotoxy(map->width * 2 + 2, y + 1);
        printf(RIGHT_WALL);
    }

    gotoxy(0, map->height + 1);
    printf(LEFT_CORNER);
    for (int x = 0; x < map->width; x++) {
        printf(TOP_BOTTOM_WALL);
    }
    printf(RIGHT_CORNER);
}

void initGame(Snake *snake, Point *food, Map *map)
{
    // drawBoarder();
    map->height = config.map_height;
    map->width = config.map_width;
    for (int x = 0; x < map->width; x++)
    {
        for (int y = 0; y < map->width; y++)
        {
            map->barrier[x][y] = 0;
        }
    }
    snake->length = 1;
    snake->body[0].x = map->width / 2;
    snake->body[0].y = map->height / 2;
    snake->direction = RIGHT;

    food->x = rand() % map->width;
    food->y = rand() % map->height;
}
void drawBoard(Snake *snake, Point *food, Map *map)
{
    // clearScreen();
    drawBoarder(map);
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            gotoxy(x * 2 + 2, y + 1);
            int isBody = 0;
            for (int k = 0; k < snake->length; k++) {
                if (snake->body[k].x == x && snake->body[k].y == y) {
                    isBody = 1;
                    break;
                }
            }

            if (map->barrier[x][y] == 1) {
                printf(BARRIER_TO_BREAK);
            } else if(map->barrier[x][y] > 0) {
                printf(BARRIER);
            } else if (isBody) {
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

void moveSnake(Snake *snake, Map *map) {
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

    if (snake->body[0].x >= map->width) snake->body[0].x = 0;
    if (snake->body[0].x < 0) snake->body[0].x = map->width - 1;
    if (snake->body[0].y >= map->height) snake->body[0].y = 0;
    if (snake->body[0].y < 0) snake->body[0].y = map->height - 1;
}

int checkCollision(Snake *snake, Map *map) {
    if (map->barrier[snake->body[0].x][snake->body[0].y] > 0)
        return 1;
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}

int updateDirection(Snake *snake) {
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
        case 'q':
            return 1;
        default:
            break;
    }
    return 0;
}

int errorFood(Snake *snake,Point *food, Map *map) {
    if (map->barrier[food->x][food->y] > 0) return 1;
    for (int i = 1; i < snake->length; i++) {
        if (food->x == snake->body[i].x && food->y == snake->body[i].y) {
            return 1;
        }
    }
    return 0;
}

int eatFood(Snake *snake, Point *food, Map *map)
{
    if (snake->body[0].x == food->x && snake->body[0].y == food->y) {
        for(int x=0; x<map->width; x++) {
            for(int y=0; y<map->width; y++) {
                if(map->barrier[x][y] > 0)
                    map->barrier[x][y]--;
            }
        }
        for (int i = 0; i < snake->length; i++)
        {
            int x = snake->body[i].x, y = snake->body[i].y;
            if (map->barrier[x][y] == 0)
                map->barrier[x][y] = config.barrier_delay;
        }
        snake->length++;
        food->x = rand() % map->width;
        food->y = rand() % map->height;
        // BUG: food refresh in the snake body
        while(errorFood(snake,food, map)){
            food->x = rand() % map->width;
            food->y = rand() % map->height;
        }
        return 1;
    }
    return 0;
}