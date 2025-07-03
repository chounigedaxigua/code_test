#include "tcp_connect.h"
#if 0

int connect_task(struct sockaddr_in st_clnsock,int i_sockfd,uint16_t port)
{
    if((i_sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)	//建立套接字
	{
		printf("socket Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(0);
	}


	memset(&st_clnsock, 0, sizeof(st_clnsock));
	st_clnsock.sin_family = AF_INET;  //IPv4协议
	//IP地址转换(直接可以从物理字节序的点分十进制 转换成网络字节序)
	if(inet_pton(AF_INET, IP_ADDR, &st_clnsock.sin_addr) <= 0)
	{
		printf("inet_pton Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	st_clnsock.sin_port = htons(port);	//端口转换(物理字节序到网络字节序)

	if(connect(i_sockfd, (struct sockaddr*)&st_clnsock, sizeof(st_clnsock)) < 0)	//主动向设置的IP和端口号的服务端发出连接
	{
		printf("connect Error: %s (errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
    return CONNECT_OK;
}
#endif
