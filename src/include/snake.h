#ifndef SNAKE_H
#define SNAKE_H

#include "structs.h"

// Game logic related functions
void initGame(Snake *snake, Point *food, Map *map);
void drawBoarder(Map *map);
void drawBoard(Snake *snake, Point *food, Map *map);
void moveSnake(Snake *snake, Map *map);
int checkCollision(Snake *snake, Map *map);
int updateDirection(Snake *snake);
int eatFood(Snake *snake, Point *food, Map *map);

#endif // SNAKE_H