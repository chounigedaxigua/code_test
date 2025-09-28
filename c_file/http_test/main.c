#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // close()
#include <sys/socket.h> // socket(), bind(), listen(), accept()
#include <netinet/in.h> // struct sockaddr_in, htons(), INADDR_ANY
#include <arpa/inet.h>  // inet_ntoa()

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello, World!\r\n";

    // 1. 创建 socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. 设置 socket 选项（允许端口复用）
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 3. 配置服务器地址结构
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 监听所有网络接口
    address.sin_port = htons(PORT);       // 设置端口

    // 4. 绑定 socket 到指定地址和端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 5. 开始监听连接
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("HTTP Server is running on http://localhost:%d\n", PORT);
    printf("Waiting for a client to connect...\n");

    // 6. 接受客户端连接
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // 打印客户端 IP 地址
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Client connected from %s:%d\n", client_ip, ntohs(address.sin_port));

    // 7. 读取客户端发送的数据（HTTP 请求）
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Received request:\n%s\n", buffer);

    // 8. 向客户端发送 HTTP 响应
    send(client_fd, response, strlen(response), 0);
    printf("Response sent.\n");

    // 9. 关闭连接
    close(client_fd);
    close(server_fd);

    return 0;
}