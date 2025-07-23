#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/unistd.h>
#include "ev.h"
 
void timer_action(struct ev_loop *main_loop,ev_timer *time_w,int e)
{
    puts("In Time action");
    // ev_break (main_loop, EVBREAK_ONE);
    // ev_timer_stop(main_loop,time_w);
}
 
int main(int argc,char **argv)
{
    ev_timer timer_w;   
    struct ev_loop *main_loop = ev_default_loop(0);
 
    ev_init(&timer_w,timer_action);
    ev_timer_set(&timer_w,0,2);//第二个参数表示多次时间执行第一次回调函数，第三个参数表示循环周期
 
    ev_timer_start(main_loop,&timer_w);
 
    ev_run(main_loop,0);
    return 0;
}