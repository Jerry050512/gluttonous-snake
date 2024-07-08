#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "game.h"
#include "macros.h"
#include "utils.h"
#include "snake.h"
#include "stats.h"
#include "structs.h"

extern Config config;

void playGame() {
    Snake snake;
    Point food;
    
    reset_score_count();
    reset_step_count();
    srand(time(NULL));
    hideCursor();
    initGame(&snake, &food);

    while (1) {
        if (kbhit()) {
            updateDirection(&snake);
        }
        moveSnake(&snake);
        increment_step_count();
        if (checkCollision(&snake)) {
            gotoxy(0, config.map_height+2);
            printf("Game Over! Your score is: %d\n", get_score_count());
            printf("AND Your STEP is: %d\n", get_step_count());
            press_any_key_to_continue();
            break;
        }

        if (eatFood(&snake, &food)) {
            increment_score_count();
        }

        drawBoard(&snake, &food);
        usleep(config.sleep_time); // 100 milliseconds
    }

    showCursor();
}
