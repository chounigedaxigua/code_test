//
// Created by user on 2022/8/17.
//

#include "stack.h"


void init(sqtack *sq){   //初始化栈
    sq->top = -1;
}

bool push(sqtack *sq,int *x){
    if(sq->top + 1 == MaxSize)
        return false;
    sq->data[++sq->top] = *x;
    return true;
}

bool pop(sqtack *sq,int *x){
    if(sq->top == -1)
        return false;
    *x = sq->data[sq->top--];
    return true;
}


