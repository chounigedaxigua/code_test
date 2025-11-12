#include "task.h"

static int default_check_func(void *arg)
{
    return 0;
}
task_t* task_creat(char *description,task_work_t work,task_check_t check,void *data)
{
    if (!work) return NULL;
    task_t *task = (task_t*)malloc(sizeof(task_t));
    task->description = description;
    task->check       = check ? check : default_check_func;
    task->work        = work;
    task->data        = data;
    return task;
}

// int task_open(task_t * task)
// {

// }
