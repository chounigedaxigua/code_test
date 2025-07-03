/*
 * 接收到版本，将版本存放到bin_version文件夹下，删除bin文件夹下的所有文件，并将bin文件夹下的bin文件烧录到MCU
 * 1、烧录函数
 * 2、文件名获取函数
 * 3、......
 *
 *
 * */
#include "tcp/tcp_connect.h"

#include <iostream>
#include <string>
#include <string.h>
#include <filesystem>
#include <stdlib.h>

#define CMD_MAX_LEN
std::string _program = "./program_bin.sh ";
std::string _filename = "bin/H61V0.010.01-FForSoc_0X63F0F071.bin";
std::string _cmd = {0};
char cmd[CMD_MAX_LEN] = {0};

extern const int flag; // 0表示读写处于阻塞模式
extern const int port;
extern const int buffer_size;
/*烧录函数*/
int program_bin(void)
{
	_cmd = _program + _filename;
	strcpy(cmd,_cmd.c_str());
	system(cmd);
}
/*bin文件名获取函数*/
void get_filename()
{
	
}
int main(int argc, const char* argv[])
{
    // 创建服务器监听的套接字。Linux下socket被处理为一种特殊的文件，返回一个文件描述符。
    // int socket(int domain, int type, int protocol);
    // domain设置为AF_INET/PF_INET，即表示使用ipv4地址(32位)和端口号（16位）的组合。
    int server_sockfd = socket(PF_INET,SOCK_STREAM,0);  
    if(server_sockfd == -1)
	{
        close(server_sockfd);
        perror("socket error!");
    }
    // /* Enable address reuse */
    // int on = 1;
    // int ret = setsockopt( server_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

    // 此数据结构用做bind、connect、recvfrom、sendto等函数的参数，指明地址信息。
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr)); // 结构体清零
    server_addr.sin_family = AF_INET;  // 协议
    server_addr.sin_port = htons(port);  // 端口16位, 此处不用htons()或者错用成htonl()会连接拒绝!!
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 本地所有IP
    // 另一种写法, 假如是127.0.0.1
    // inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);


    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); 
    // bind()函数的主要作用是把ip地址和端口绑定到套接字(描述符)里面
    // struct sockaddr是通用的套接字地址，而struct sockaddr_in则是internet环境下套接字的地址形式，二者长度一样，都是16个字节。二者是并列结构，指向sockaddr_in结构的指针也可以指向sockaddr。
    // 一般情况下，需要把sockaddr_in结构强制转换成sockaddr结构再传入系统调用函数中。
    if(bind(server_sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
	{
        close(server_sockfd);
        perror("bind error");
    }
    // 第二个参数为相应socket可以排队的准备道来的最大连接个数
    if(listen(server_sockfd, 5) == -1)
	{
        close(server_sockfd);
        perror("listen error");
    }
    printf("Listen on port %d\n", port);
    while(1)
	{
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        // accept()函数从处于established状态的连接队列头部取出一个已经完成的连接，
        // 如果这个队列没有已经完成的连接，accept()函数就会阻塞当前线程，直到取出队列中已完成的客户端连接为止。
        int client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);
        
        // 为完成的连接新建立一个线程
        std::thread tcpThread(requestHandling, client_sockfd, client_addr);
        tcpThread.detach(); // 不阻塞主线程，执行tcp通讯的线程从线程对象分离
    }
    close(server_sockfd);

    return 0;
}
// // int main()
// // {
// // 	int fd;
	
// // 	tcp_connect(fd);
// //	program_bin();
// // 	return 0;
// // }

