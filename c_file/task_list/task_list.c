#include "task_list.h"

task_list_t *task_list = NULL;
pthread_mutex_t counter_mutex;

int task_add(task_t * task)
{
    if(!task) return -1;
    pthread_mutex_lock(&counter_mutex);
    task_list_t *node = (task_list_t*)malloc(sizeof(task_list_t));
    node->task = task;
    static task_list_t *q = NULL;
    q = task_list;
    if(!task_list)
    {
        task_list = node;
        task_list->next = NULL;
    }
    else
    {
        while(q->next != NULL)
        {
            q = q->next;
        }
        q->next = node;
        q = q->next;
        q->next = NULL;
    }
    pthread_mutex_unlock(&counter_mutex);
    return 0;
}

void* work_handle(void *arg)
{

    while(1)
    {
        task_list_t *p = task_list;
        if(task_list)
        {
            task_list = task_list->next;
        }
        
        if(p)
        {
            if(p->task->check(p->task->data) == 0)
            {
                p->task->work(p->task->data);
            }
        }
        
        if(p)
        {
            free(p);
        }
        sleep(1);
    }
}