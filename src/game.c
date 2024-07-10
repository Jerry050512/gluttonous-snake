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
    Map map;
    
    reset_score_count();
    reset_step_count();
    srand(time(NULL));
    initGame(&snake, &food, &map);

    while (1) {
        if (kbhit()) {
            updateDirection(&snake);
        }

        if (eatFood(&snake, &food, &map)) {
            increment_score_count();
        }
        moveSnake(&snake, &map);
        increment_step_count();
        if (checkCollision(&snake, &map)) {
            gotoxy(0, map.height+2);
            printf("Game Over! Your score is: %d\n", get_score_count());
            printf("AND Your STEP is: %d\n", get_step_count());
            press_space_to_continue();
            break;
        }

        drawBoard(&snake, &food, &map);
        usleep(config.sleep_time); // 100 milliseconds
    }
}
