#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int pid;
    
    pipe(fd);
    
    pid = fork();
    
    if(pid == 0)
    {
        close(STDOUT_FILENO);
        
        close(fd[0]);
        dup(fd[1]);
        execlp("ls", "ls", "-lh", (char *) NULL);
    }
    else
    {
        close(STDIN_FILENO);
        close(fd[1]);
        dup(fd[0]);
        execlp("wc", "wc", (char *) NULL);
    }
}

