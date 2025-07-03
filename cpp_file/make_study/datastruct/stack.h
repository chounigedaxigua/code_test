//
// Created by user on 2022/8/17.
//

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 32    //最大栈深度
typedef struct sq{      //栈
    int data[MaxSize];
    int top;
}sqtack;
void init(sqtack *sq);    //初始化栈

bool push(sqtack *sq,int *x);   //进栈

bool pop(sqtack *sq,int *x);    //出栈
#endif //STACK_H

