#include "tcp_connect.h"

struct sockaddr_in  servaddr;

const int flag = 0;
const int port = 6666;
const int buffer_size = 1<<20;

const std::string SERVER_URL = "192.168.20.2";
#if 1

void tcp_server_init(int server_fd,struct sockaddr_in *server_addr,int port)
{
    memset(server_addr,0,sizeof(struct sockaddr_in));
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(port);
    server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(server_fd,(struct sockaddr*)server_addr,sizeof(struct sockaddr_in)) == -1)
	{
        close(server_fd);
        perror("bind error");
    }

    if(listen(server_fd, 5) == -1)
	{
        close(server_fd);
        perror("listen error");
    }

}

void requestHandling(const int client_sockfd, const struct sockaddr_in& client_addr)
{
    char ipbuf[128];
    printf("Connect client iP: %s, port: %d\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, 
        sizeof(ipbuf)), ntohs(client_addr.sin_port));

    char buf[buffer_size];
    while(1) 
    {

        int len = recv(client_sockfd, buf, sizeof(buf),flag);
        if (len == -1)
        {
            close(client_sockfd);
            // close(server_sockfd);
            perror("read error");
        }else if(len == 0)
        {
            break;
        }
        send(client_sockfd,buf,strlen(buf),0);
        std::cout<<buf<<std::endl;

        memset(buf,'\0',len);
    }
    close(client_sockfd);

}
#endif
void recive_handle(const int sockefd){
    char buf[buffer_size];
    while(1) 
    {

        int len = recv(sockefd, buf, sizeof(buf),flag);
        if (len == -1)
        {
            close(sockefd);
            // close(server_sockfd);
            perror("read error");
        }else if(len == 0)
        {
            break;
        }
        send(sockefd,buf,strlen(buf),0);
        std::cout<<buf<<std::endl;

        memset(buf,'\0',len);
    }
    close(sockefd);
}

int connect_to_server(const char* serverIp, int serverPort) {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    
    if(inet_pton(AF_INET, serverIp, &serverAddr.sin_addr)<=0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(sock);
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        close(sock);
        return -1;
    }

    std::cout << "Connected to the server" << std::endl;
    return sock; 
}

bool check_connection(int socket_fd) {

    if (shutdown(socket_fd, SHUT_RDWR) == -1) {
        if (errno == ENOTCONN) {
            return true;
        }
        return false;
    }
    return false;
}


void reconnect(const std::string& server, int port) {

    connect_to_server(server.c_str(),port);
    // std::cout << "Attempting to reconnect..." << std::endl;
}

void monitor_and_reconnect(const std::string& server, int port) {
    // while (true) {
    //     if (!check_connection(server,port)) {
    //         reconnect(server,port);
    //     }
    //     std::this_thread::sleep_for(std::chrono::seconds(5));
    // }
}
