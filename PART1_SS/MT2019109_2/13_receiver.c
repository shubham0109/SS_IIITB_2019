#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int sig)
{
    if(sig == SIGSTOP)
        printf("Caught SIGSTOP signal.\n");
}

int main(int argc, char const *argv[])
{
    printf("pid of the process: %d\n", getpid());
    typedef void (*handler_t)(int);
    
    if (signal(SIGSTOP, (handler_t)handler) < 0){
        printf("err");
    }
    
    sleep(100);
    exit(EXIT_SUCCESS);
}

