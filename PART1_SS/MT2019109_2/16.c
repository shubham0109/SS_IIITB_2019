#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    char buff[80], buff1[80];
    int fd1[2], fd2[2];
    pid_t pid;
    
    pipe(fd1);
    pipe(fd2);
    
    pid = fork();
    if(pid > 0)
    {
        printf("here1\n");
        close(fd1[1]);
        read(fd1[0], buff, sizeof(buff));
        printf("Message from the child: %s\n", buff);
        close(fd1[0]);
        
        close(fd2[0]);
        printf("Enter the message to the Child: ");
        scanf(" %s", buff1);
        
        write(fd2[1], buff1, sizeof(buff1));
        close(fd2[1]);
    }
    else
    {
        printf("here2\n");
        close(fd1[0]);
        printf("Enter the message to the Parent: ");
        scanf(" %s", buff);
        write(fd1[1], buff, sizeof(buff));
        close(fd1[1]);
        
        close(fd2[1]);
        read(fd2[0], buff1, sizeof(buff1));
        printf("Message from parent: %s\n", buff1);
        close(fd2[0]);
    }

    return 0;
}

