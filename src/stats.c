#include "stats.h"

static int step_count = 0;
static int score_count = 0;

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
void reset_score_count()
{
    score_count = 0;
}

void increment_score_count()
{
    score_count++;
}

int get_score_count()
{
    return score_count;
}