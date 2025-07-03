#include <stdio.h>
#include <stdlib.h>
#define NAME_MAX_LEN 128
static int custom_num = 0;
typedef struct _custom
{
    char name[NAME_MAX_LEN];
    char id_card_num[18];
    int balance;

}custom_t;

typedef struct _custom_list
{
    struct _custom_list *next;
    // custom_t info;
    int data;
    
}custom_list_t;

custom_list_t* custom_list_node_creat(int _data)
{

    custom_list_t* node = (custom_list_t*)malloc(sizeof(custom_list_t));
    node->next = NULL;
    node->data = _data;
    //init data
    return node;
}

int custom_list_insert(custom_list_t *NODE,int _data)
{
    custom_list_t *p = (custom_list_t*)NODE;
    custom_list_t * temp = (custom_list_t*)malloc(sizeof(custom_list_t));
    temp->data = _data;
    temp->next = p->next;

    p->next = temp;
    return 0;

}
void custom_list_distory(custom_list_t *NODE)
{
    if(NODE == NULL)
        return;
    custom_list_t *p = NODE;
    custom_list_t *q = NODE->next;
    while(q != NULL)
    {
        free(p);
        p = q;
        q = q->next;
    }
    free(p);
}
void custom_list_show(custom_list_t *NODE)
{
    custom_list_t *q = NODE;
    while(q!=NULL)
    {
        printf("%d\n",q->data);
        q = q->next;
    }
}
int main()
{

    custom_list_t *cl = custom_list_node_creat(10086);
    for(int i = 0;i<10;i++)
    {
        custom_list_insert(cl,i);
    }
    
    custom_list_show(cl);

    custom_list_distory(cl);
    return 0;
}