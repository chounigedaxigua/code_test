#include "tcp_connect.h"

struct sockaddr_in  servaddr;

const int flag = 0; // 0表示读写处于阻塞模式
const int port = 6666;
const int buffer_size = 1<<20;



void requestHandling(const int client_sockfd, const struct sockaddr_in& client_addr)
{
    char ipbuf[128];
    printf("Connect client iP: %s, port: %d\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, 
        sizeof(ipbuf)), ntohs(client_addr.sin_port));

    // 实现客户端发送小写字符串给服务端，服务端将小写字符串转为大写返回给客户端
    char buf[buffer_size];
    while(1) 
    {
        // read data, 阻塞读取
        int len = recv(client_sockfd, buf, sizeof(buf),flag);
        if (len == -1)
         {
            close(client_sockfd);
            // close(server_sockfd);
            perror("read error");
        }else if(len == 0)// 这里以len为0表示当前处理请求的客户端断开连接
        {  
            break;
        }
        printf("Recvive from client iP: %s, port: %d， str = %s\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, 
        sizeof(ipbuf)), ntohs(client_addr.sin_port),buf);
        // 小写转大写
        for(int i=0; i<len; ++i) 
        {
            buf[i] = toupper(buf[i]);
        }
        printf("Send to client iP: %s, port: %d， str = %s\n",inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, 
        sizeof(ipbuf)), ntohs(client_addr.sin_port), buf);

        // 大写串发给客户端
        if(send(client_sockfd, buf, strlen(buf),flag) == -1)
        {
            close(client_sockfd);
            // close(server_sockfd);
            perror("write error");
        }
        memset(buf,'\0',len); // 清空buf
    }
    close(client_sockfd);
    printf("Disconnect client iP: %s, port: %d\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, 
        sizeof(ipbuf)), ntohs(client_addr.sin_port));
}
