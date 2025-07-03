#include "thread_task.h"
 

void* ptintf_hello_world(void* tid){
	printf("Hello world %d.\n",tid);
	int* a=(int*)malloc(sizeof(int));
	*a=(int)tid*(int)tid;
	return a;	//线程函数的返回值 
}
