#ifndef _TASK_H_
#define _TASK_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
typedef int (*task_work_t)(void *arg);
typedef int (*task_check_t)(void *arg);
typedef struct _task_t
{
    char *description;
    void *data;
    task_work_t check;
    task_check_t work;
}task_t;

task_t* task_creat(char *description,task_work_t work,task_check_t check,void *data);
#endif