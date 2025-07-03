#include <stdio.h>
#include <pthread.h>
#include "thread_task.h"

int main(void){

	int a;

    pthread_t threads[NUMBER_OF_THREADS];
    int status,i;
    for(i=0;i<NUMBER_OF_THREADS;i++){
    	// printf("Main here. Creating thread %d\n",i);
    	status=pthread_create(&threads[i],NULL,ptintf_hello_world,(void*)i);

		if(status!=0){
    		printf("pthread_create returned error code %d\n",status);
    		exit(-1);
		}
	}
	// for(int i=0;i<NUMBER_OF_THREADS;i++)
	// {
	// 	int** res=(int**)malloc(sizeof(int*));
	// 	pthread_join(threads[i],(void**)res);
    // 	printf("res[%d]:%d\n",i,**res);//打印线程函数的返回值 
	// 	free(*res); //释放线程处理函数中使用malloc分配的内存空间 
	// }
	scanf("%d",&a);
}
