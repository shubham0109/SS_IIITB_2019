#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void f()
{
    printf("Catched SIGFPE signal\n");
}

int main()
{
    struct sigaction sg;
    sg.sa_sigaction = f;
    sigaction(SIGFPE, &sg, NULL);
    kill(getpid(), SIGFPE);
    
    return 0;
}


