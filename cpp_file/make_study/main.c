#include <stdio.h>
#include "datastruct/stack.h"
#include "datastruct/linklist.h"
#include "function/digitaldeal.h"
#include "function/stringdeal.h"
#include "datastruct/bttree.h"

int main() {
    linklist *head;

    decimaltobinary(10086);

    int arr[] = {87,98,86,84,92,9};

    quicksort(arr,0,(sizeof (arr)/sizeof (int))-1);
    printf("快速排序完成：\n ");
    for (int i = 0; i < sizeof (arr)/sizeof (int); ++i) {
        printf("%d ",arr[i]);
    }
    printf("\n");


    head = (linklist*)malloc(sizeof (linklist));//只能在外面给头节点分配地址,如果在函数headinsert中分配就会出问题
    head->next = NULL;          //这一步一定要有，而且还只能给头节点分配地址之后

    for (int i = 0; i < sizeof (arr)/sizeof (int); ++i) {
        *head = headinsert(head,arr[i]);
    }
    linklist *p;
    p=head->next;
    //*head = deletelement(head,92);
    printf("用数组元素建立链表并将数据并打印链表中的数据：\n");
    while(p != NULL){   //这里绝对不能用while(p->next != NULL) 不然的话最后一个元素输不出来
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    char *ch = "hello world !!!" ;
    printf("字符串长度为:%d\n", strlen(ch));
    int x = qiuzuichanghuiwenshu(ch);
    printf("最长回文数长度为:%d", x);



    BiTree bt;
    //create_bintree(&bt);

    return 0;
}

