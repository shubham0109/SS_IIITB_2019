#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void f(int sig)
{
    switch(sig)
    {
        case SIGINT: printf("SIGINT.\n");
            break;
        default: printf("Error\n");
    }
}

int main()
{
    signal(SIGINT,f);
    
    kill(getpid(), SIGINT);
    
    return 0;
}


