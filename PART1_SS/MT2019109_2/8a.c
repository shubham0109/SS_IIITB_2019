#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void f(int sig)
{
    switch(sig)
    {
        case SIGSEGV: printf("SIGSEGV.\n");
            break;
        default: printf("Error\n");
    }
}

int main()
{
    signal(SIGSEGV,f);
    
    kill(getpid(), SIGSEGV);
    
    return 0;
}

