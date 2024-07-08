#ifndef SNAKE_H
#define SNAKE_H

#include "structs.h"

void initGame(Snake *snake, Point *food);
void drawBoarder();
void drawBoard(Snake *snake, Point *food);
void moveSnake(Snake *snake);
int checkCollision(Snake *snake);
void updateDirection(Snake *snake);
int eatFood(Snake *snake, Point *food);

#endif