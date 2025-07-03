#ifndef TCP_CONNECT_H_
#define TCP_CONNECT_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>

enum connect_retStatus{
    CONNECT_OK,
    CONNECT_ERR

};
#define SERVER_PORT 6666

#endif // !TCP_CONNECT_H_
