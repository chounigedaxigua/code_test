#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main()
{
    int pid = 0;
    if(pid = fork() < 0)
    {
        return -1;

    }
    printf("hello\n");
}