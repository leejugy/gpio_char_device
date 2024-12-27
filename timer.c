#include "timer.h"
struct timespec expire_time[MAX_TIMER_NUM] = {
    0,
};

void set_timer_ms(int set_time, TIMER_INDEX index)
{
    struct timespec time_sp;

    clock_gettime(CLOCK_REALTIME, &time_sp);
    expire_time[index].tv_sec = time_sp.tv_sec;
    expire_time[index].tv_nsec = time_sp.tv_nsec + set_time * 1000 * 1000;

    if (expire_time[index].tv_nsec >= 1000 * 1000 * 1000)
    {
        expire_time[index].tv_sec++;
        expire_time[index].tv_nsec %= 1000000000;
    }
}

int check_expired(TIMER_INDEX index)
{
    struct timespec time_sp;

    clock_gettime(CLOCK_REALTIME, &time_sp);

    if (expire_time[index].tv_sec < time_sp.tv_sec)
    {
        return 1;
    }
    else if (expire_time[index].tv_sec == time_sp.tv_sec && expire_time[index].tv_nsec <= time_sp.tv_nsec)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int timer_init()
{
    TIMER_INDEX i = 0;
    memset(expire_time, 0, sizeof(expire_time));
}