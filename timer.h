#ifndef __TIMER__
#define __TIMER__

#include <time.h>
#include <stdio.h>
#include <string.h>
typedef enum
{
    TIMER_GPIO,
    TIMER_GPIO_SLEEP,
    MAX_TIMER_NUM,
} TIMER_INDEX;

void set_timer_ms(int set_time, TIMER_INDEX index);
int check_expired(TIMER_INDEX index);
int timer_init();

#endif