#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define  SHMKEY  75
int  shmid,i;   


struct info
{
    char name[20];
    int num;
    int data;
};
struct info *addr;
void  shmw()
{
    int i=0; 
    shmid=shmget(SHMKEY,1024,0777);      /*打开共享存储区*/
    addr=(struct info*)shmat(shmid,0,0);           /*获得共享存储区首地址*/
    memset(addr,0,sizeof(struct info));
    addr->num = 1000;
    addr->data = 0;
    for (i = 0;i <= 9;++i)
    {
        addr->data += 1;
        sprintf(addr->name,"name__%c__",'a'+i);
        ++addr->num;
        printf("(write) data_w->name = %s,data_w->num = %d,data_w->data = %d\n",addr->name,addr->num,addr->data);
        sleep(1);
    }
    exit(0);
}
int main( )
{

    shmw();

    return 0;
}
