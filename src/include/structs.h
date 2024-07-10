#ifndef STRUCTS_H
#define STRUCTS_H

#include "macros.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[400];
    int length;
    int direction;
} Snake;

typedef struct {
    int width;
    int height;
    int barrier[MAX_MAP_WIDTH_HEIGHT][MAX_MAP_WIDTH_HEIGHT];
} Map;

typedef struct {
    int map_width;
    int map_height;
    int init_length;
    int barrier_delay;
    int sleep_time;
} Config;

#endif