#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        kill(getppid(), SIGKILL);
        sleep(1);
    else
    {
        printf("pid of parent: %d\n", getpid());
        sleep(3);
    }
}

