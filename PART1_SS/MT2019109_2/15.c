#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buff[80];
    int fd[2];
    pid_t pid;
    
    pipe(fd);
    pid = fork();
    
    if(pid > 0){
        close(fd[0]);
        printf("Enter the message to the child: ");
        scanf("%s", buff);
        write(fd[1], buff, sizeof(buff));
        close(fd[1]);
    }
    else{
        close(fd[1]);
        read(fd[0], buff, sizeof(buff));
        printf("Message from the parent: %s\n", buff);
        close(fd[0]);
    }
    
    return 0;
}

