#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  SHMKEY  75
int  shmid,i;   
// int  *addr;
struct info
{
    char name[20];
    int num;
    int data;
}; 
struct info *addr;
void  shmr()
{
    struct info *addr = (struct info *)malloc(sizeof(struct info));
    memset(addr,0,sizeof(struct info));
    shmid=shmget(SHMKEY,1024,0777|IPC_CREAT);
    addr=(struct info*)shmat(shmid,0,0);        /*获取首地址*/
    do 
    {
        
        strcpy(addr->name,"haha");
        while (0 == strcmp(addr->name,"haha"));
        // data_r = (struct info *)addr;
        printf("(read) addr->name = %s,addr->num = %d,addr->data = %d\n",addr->name,addr->num,addr->data);
    }while (addr->data != 10);

    
    shmctl(shmid,IPC_RMID,0);     /*撤消共享存储区，归还资源*/
    exit(0);
}
 
int main( )
{
  
    shmr();
    return 0;
}
