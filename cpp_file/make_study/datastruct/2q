//
// Created by user on 2022/8/17.
//

#include "linklist.h"

linklist headinsert(linklist *head,int x)//从头节点插入元素到单链表
{
    linklist *s;
        s = (linklist*)malloc(sizeof (linklist));
        s->data = x;
        s->next = head->next;
        head->next = s;
    return *head;
}
//linklist deletelement(linklist *head,int e){
//    linklist *p;
//    p = NULL;
//    p = head->next;
//    while(p != NULL){
//        if(p->next->data = e){
//            p->next = p->next->next;
//        }
//    }
//    return *head;
//}
