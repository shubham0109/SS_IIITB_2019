#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8888

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
    
    listen(socket_fd, 10);
    
    while(1)
    {
        conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);
        int pid;
        pid = fork();
        
        if(pid == 0)
        {
            int var;
            close(socket_fd);
            read(conn_fd, &var, sizeof(int));
            
            if(write(conn_fd, &sum, sizeof(sum)) == -1) ERR_EXIT("write()");
            if(close(conn_fd) == -1) ERR_EXIT("close()");
            exit(EXIT_SUCCESS);
        }
        else
        { // parent close the connection
            if(close(conn_fd) == -1) ERR_EXIT("close()");
        }
    }
    close(socket_fd);
}

