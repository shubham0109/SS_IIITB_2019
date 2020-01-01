#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int socket_fd;
    ssize_t n;
    char recvBuff[1024];
    struct sockaddr_in server_addr;
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&server_addr, '0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    
    
    connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    int val;
    write(socket_fd, &val, sizeof(val));
    read(socket_fd, &val, sizeof(val));
    val = ntohl(val);
    printf("Sum of numbers: %d\n", val);
    close(socket_fd);
    exit(EXIT_SUCCESS);
}

