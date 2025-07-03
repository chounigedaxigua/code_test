//
// Created by user on 2022/8/17.
//

#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
typedef struct Node{  //链表
    int data;
    struct Node *next;
}linklist;

linklist headinsert(linklist *head,int x);   //头节点创建单链表
linklist deletelement(linklist *head,int e);
#endif //LINKLIST_H

