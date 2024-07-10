#include <stdio.h>
#include <unistd.h>

#include "menu.h"
#include "utils.h"
#include "game.h"
#include "settings.h"

extern Config config;

int show_option(char prompts[][50], int n) {
    int option=0;
    while(1) {
        for(int i=0; i<n; i++) {
            gotoxy(0, i+1);
            printf("  ");
            if(option == i) {
                printf("> ");
            } else {
                printf("  ");
            }
            printf("%s\n", prompts[i]);
        }
        if(kbhit()) {
            int ch = getch();
            gotoxy(0, 4);
            printf("  ");
            switch (ch)
            {
            case 'w':
                option = (option + n - 1) % n;
                break;
            case 's':
                option = (option + 1) % n;
                break;
            case ' ':
                clearScreen();
                gotoxy(0, 0);
                return option;
            default:
                break;
            }
        }
        usleep(10000);
    }
}

int choose_option() {
    clearScreen();
    char prompts[][50] = {"Start Game", "Help", "Settings", "Exit"};
    gotoxy(0, 0);
    printf("Welcome to Gluttonous Snake Game!");
    return show_option(prompts, 4);
}

void display_help_menu() {
    clearScreen();
    gotoxy(0, 0);   
    printf("Use 'w', 'a', 's', 'd' to move\n");
    printf("Snake shed their skin(that is,obstacles)after each meal.Do not touch it!\n");
    printf("Customize the game settings,eat as much as possible and go further!\n");
    printf("");
    press_any_key_to_continue();
}

int display_settings_menu() {
    clearScreen();
    char prompts[][50] = {"Change Map Size", "Change Snake Speed", "Change init length", "Change Barrier Delay", "Back"};
    int option = show_option(prompts, 5);
    switch (option)
    {
    case 0:
        int width, height;
        printf("Input Map Size (default max 20x20): ");
        scanf("%dx%d", &width, &height);
        if(width > MAX_MAP_WIDTH_HEIGHT || height > MAX_MAP_WIDTH_HEIGHT ||
           width <= 0 || height <= 0) {
            printf("Invalid Map Size\n");
            break;
        }
        printf("Set Map Size to %dx%d\n", width, height);
        adjust_map_size(width, height, &config);
        break;
    case 1:
        int speed;
        printf("Input Snake Speed (default 2 max 3): ");
        scanf("%d", &speed);
        if(speed > 3 || speed < 1) {
            printf("Invalid Snake Speed\n");
            break;
        }
        printf("Set Snake Speed to %d\n", speed);
        switch (speed) 
        {
        case 1:
            speed = 300000;
            break;
        case 2:
            speed = 100000;
            break;
        case 3:
            speed = 50000;
            break;
        }
        set_snake_speed(speed, &config);
        break;
    case 2:
    	int init_length;
        printf("Input Initial Length (default 3 max 20): ");
        scanf("%d", &init_length);
        if(init_length > 20 || init_length < 1) {
            printf("Invalid Initial Length\n");
            break;
        }
        printf("Set Initial Length to %d\n", init_length);
        set_init_length(init_length, &config);
        break;
    case 3:
    	int barrier_delay;
        printf("Input Barrier Delay (default 0 max 7): ");
        scanf("%d", &barrier_delay);
        if(barrier_delay > 7 || barrier_delay < 0) {
            printf("Invalid Barrier Delay\n");
            break;
        }
        printf("Set Barrier Delay to %d\n", barrier_delay);
        set_barrier_delay(barrier_delay, &config);
        break;
    case 4:
        return 0;
    default:
        break;
    }
    write_config(&config);
    printf("Settings saved...\n");
    press_any_key_to_continue();
    return 1;
}

int display_menu() {
    int option = choose_option();
    printf("option=%d\n", option);
    printf("Loading...\n");
    usleep(100000);
    switch (option)
    {
    case 0:
        playGame();
        break;
    case 1:
        display_help_menu();
        break;
    case 2:
        while(display_settings_menu()) ;
        break;
    case 3:
        printf("Exiting...\n");
        return 0;
    default:
        break;
    }
    return 1;
}