//
// Created by user on 2022/8/17.
//

#include "digitaldeal.h"
sqtack sq01;
void decimaltobinary(int x){   // 十进制转二进制
    int s,e;
    while(x != 0){
        s = x%2;
        push(&sq01,&s);
        x = x/2;
    }
    while(sq01.top != -1){
        pop(&sq01,&e);
        printf("%d",e);
    }
    printf("\n");
}

int partition(int a[],int low,int high){    //快排,划分枢轴元素
    int pivot = a[low];
    while(low < high){
        while(low < high && a[high] >= pivot)//从小到大排序
            --high;
        a[low] = a[high];

        while(low < high && a[low]<=pivot)
            ++low;
        a[high] = a[low];
    }
    a[low] = pivot;
    return low;
}
void quicksort(int a[],int low,int high){      // 快排
    if(low < high){
        int pivotpos = partition(a,low,high);
        quicksort(a,low,pivotpos-1);
        quicksort(a,pivotpos+1,high);
    }
}
