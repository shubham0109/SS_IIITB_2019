#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
    
int main()
{
    int pid[3], wstatus;
    for (int i = 0; i < 3; ++i)
    {
        if((pid[i] = fork()) == -1)
        {
            perror("fork()");
            exit(EXIT_FAILURE);
        }
        else if(pid[i] == 0)
        {
            sleep(i);
            printf("child %d\n", i);
            exit(i);
        }
    }
    // waiting for 2nd process to terminate
    pid_t cpid = waitpid(pid[1], &wstatus, 0);
    if(cpid == -1)
    {
        perror("waitpid()");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(wstatus))
        printf("child with pid %d, terminated with exit status: %d\n",
               cpid, WEXITSTATUS(wstatus));
    exit(EXIT_SUCCESS);
}