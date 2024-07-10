#ifndef SETTINGS_H
#define SETTINGS_H

#include "structs.h"

void read_config(Config *config);
void create_default_config(Config *config);
void write_config(Config *config);

void adjust_map_size(int width, int height, Config *config);
void set_snake_speed(int speed, Config *config);
void set_barrier_delay(int delay, Config *config);
void set_init_length(int init_length, Config *config);

#endif // SETTINGS_H
