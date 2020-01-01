#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
# define PORT 8888

int main(int argc, char const *argv[])
{
    
    int socket_fd, conn_fd;
    struct sockaddr_in serv_addr;
    
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    
    bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    printf("listening\n");
    listen(socket_fd, 1);
    
    while(1)
    {
        conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);
        
        int pass;
        read(conn_fd, &pass, sizeof(pass));
        printf("serv pass: %d\n", pass);
        if (pass == 10){
            write(conn_fd, "correct", strlen("correct"));
        }else{
            write(conn_fd, "incorrect", strlen("incorrect"));
        }
        
        close(conn_fd);
    }
    close(socket_fd);
}

