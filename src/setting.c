#include <stdio.h>
#include <stdlib.h>

#include "settings.h"
#include "structs.h"

// Save config file in 'glu-snake.cfg'

void read_config(Config *config)
{
    FILE *fp = fopen("glu-snake.cfg", "r");

    if (fp == NULL)
    {
        create_default_config(config);
        return;
    }
    fscanf(fp, "map_height=%d\n", &config->map_height);
    fscanf(fp, "map_width=%d\n", &config->map_width);
    fscanf(fp, "init_length=%d\n", &config->init_length);
    fscanf(fp, "barrier_delay=%d\n", &config->barrier_delay);
    fscanf(fp, "sleep_time=%d\n", &config->sleep_time);
    fclose(fp);
}

void create_default_config(Config *config)
{
    config->map_height = MAX_MAP_WIDTH_HEIGHT;
    config->map_width = MAX_MAP_WIDTH_HEIGHT;
    config->init_length = 3;
    config->barrier_delay = 0;
    config->sleep_time = 100000;
    write_config(config);
}

void write_config(Config *config)
{
    FILE *fp;
    fp = fopen("glu-snake.cfg", "w");

    if (fp == NULL)
    {
        printf("File could not be opened\n");
        return;
    }

    fprintf(fp, "map_height=%d\n", config->map_height);
    fprintf(fp, "map_width=%d\n", config->map_width);
    fprintf(fp, "init_length=%d\n", config->init_length);
    fprintf(fp, "barrier_delay=%d\n", config->barrier_delay);
    fprintf(fp, "sleep_time=%d\n", config->sleep_time);
    fclose(fp);
}

void adjust_map_size(int width, int height, Config *config)
{
    config->map_width = width;
    config->map_height = height;
}

void set_snake_speed(int speed, Config *config)
{
    config->sleep_time = speed;
}

void set_barrier_delay(int delay, Config *config)
{
    config->barrier_delay = delay;
}

void set_init_length(int init_length, Config *config)
{
    config->init_length = init_length;
}