#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

#include "macros.h"
#include "utils.h"
#include "snake.h"

int main() {
    #if defined(_WIN32)
    system("chcp 65001");
    #endif
    setlocale(LC_ALL, "");
    Snake snake;
    Point food;
    int score = 0;
    
    srand(time(NULL));
    hideCursor();
    initGame(&snake, &food);

    while (1) {
        if (kbhit()) {
            updateDirection(&snake);
        }
        moveSnake(&snake);

        if (checkCollision(&snake)) {
            printf("Game Over! Your score is: %d\n", score);
            break;
        }

        if (eatFood(&snake, &food)) {
            score++;
        }

        drawBoard(&snake, &food);
        usleep(100000); // 100 milliseconds
    }

    showCursor();
    return 0;
}
