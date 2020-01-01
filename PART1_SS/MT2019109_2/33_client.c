#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8888

int main(int argc, char *argv[])
{
    int socket_fd;
    ssize_t n;
    char recvBuff[1024];
    struct sockaddr_in server_addr;
    
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&server_addr, '0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    
    if(connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("error in conn\n");
    }
    
    
    int password;
    printf("enter password\n");
    scanf("%d", &password);
    char val[10];
    write(socket_fd, &password, sizeof(password));
    read(socket_fd, &val, sizeof(val));
    printf("Password: %s\n", val);
    close(socket_fd);
    return 0;
}

