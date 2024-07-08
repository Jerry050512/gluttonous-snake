#include "settings.h"

void read_config(Config *config){
    config->map_height = 20;
    config->map_width = 20;
    config->barrier_delay = 3;
    config->sleep_time = 100000;
}
void create_default_config(Config *config){
    
}
void write_config(Config *config){
    
}

void adjust_map_size(int width, int height, Config *config){
    
}
void set_snake_speed(int speed, Config *config){
    
}
void set_barrier_delay(int delay, Config *config){
    
}