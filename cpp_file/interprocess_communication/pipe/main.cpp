//下面是C++使用管道（Pipe）进行进程间通信的一个例子：
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
using namespace std;
void read_msg(int rfd)
{
    char read_buf[32] = {0};
    int read_length = 0;
    while(1)
    {
        read_length = read(rfd,read_buf,sizeof(read_buf));
        if(read_length > 0)
        {
            read_buf[read_length] = '\0';
            std::cout << "read data = " << read_buf << std::endl;
        }
    }
}
void write_msg(int wfd)
{   
    int i = 0;
    char write_buf[32] = {0};
    while(1)
    {
        sprintf(write_buf,"I am child  %d ",++i);
        write(wfd, write_buf, sizeof(write_buf)); // 向管道写入数据
        sleep(1);
    }
}
int main() {
    int fd[2];
    pid_t pid;
    char buffer[10086] = {0};
    char read_buf[32] = {0};
    char write_buf[32] = {0};
    // 创建管道
    if (pipe(fd) < 0) {
        cerr << "Failed to create pipe." << endl;
        return 1;
    }
    // 创建子进程
    if ((pid = fork()) < 0) {
        cerr << "Failed to create child process." << endl; 
        return 2;
    } else if (pid > 0) { // 父进程
        // close(fd[1]); // 关闭写端
    
        // read(fd[0],read_buf,sizeof(read_buf));
        read_msg(fd[0]);
        // close(fd[0]);
        
        wait(NULL); // 等待子进程结束
    } else { // 子进程
        // close(fd[0]);

        write_msg(fd[1]);

        // close(fd[0]);
    }
    
    return 0;

}
