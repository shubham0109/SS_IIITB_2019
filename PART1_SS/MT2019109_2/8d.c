#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void f(int sig)
{
    switch(sig)
    {
        case SIGALRM: printf("SIGALRM.\n");
            break;
        default: printf("Error\n");
    }
}

int main()
{
    signal(SIGALRM,f);
    
    //kill(getpid(), SIGSEGV);
    alarm(3);
    pause();
    return 0;
}


