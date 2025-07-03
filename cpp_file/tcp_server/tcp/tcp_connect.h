#ifndef TCP_CONNECT_H_
#define TCP_CONNECT_H_

#include <iostream>
#include <stdio.h>
#include <cstring>       // void *memset(void *s, int ch, size_t n);
#include <sys/types.h>   // 数据类型定义
#include <sys/socket.h>  // 提供socket函数及数据结构sockaddr
#include <arpa/inet.h>   // 提供IP地址转换函数，htonl()、htons()...
#include <netinet/in.h>  // 定义数据结构sockaddr_in
#include <ctype.h>       // 小写转大写
#include <unistd.h>      // close()、read()、write()、recv()、send()...
#include <thread>		 // c++11 thread类

enum connect_retStatus{
    CONNECT_OK,
    CONNECT_ERR

};
#define SERVER_PORT 6666


void requestHandling(const int client_sockfd, const struct sockaddr_in& client_addr);
#endif // !TCP_CONNECT_H_
