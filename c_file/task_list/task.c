#include "task.h"

task_t* task_creat(char *description,task_work_t work,task_check_t check,void *data)
{
    if(!work || !check) return NULL;
    task_t *task = (task_t*)malloc(sizeof(task_t));
    task->description = description;
    task->work = work;
    task->check = check;
    task->data = data;
    // printf("%s\n",description);
    return task;
}

int task_open(task_t * task)
{

}
