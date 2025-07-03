//
// Created by user on 2022/8/19.
//

#ifndef BTTREE_H
#define BTTREE_H

#include <stdio.h>
#include <stdlib.h>
typedef struct BtNode{
    int data;
    struct BtNode *lchild,*rchild;
}BinTNode,*BiTree;

void create_bintree(BiTree *T);

#endif //BTTREE_H

