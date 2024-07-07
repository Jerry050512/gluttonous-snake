#include "stats.h"

static int step_count = 0;

void reset_step_count()
{
    step_count = 0;
}

void increment_step_count()
{
    step_count++;
}

int get_step_count()
{
    return step_count;
}
