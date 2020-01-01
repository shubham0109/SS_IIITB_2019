#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void f()
{
    printf("Catched SIGINT signal\n");
}

int main()
{
    struct sigaction sg;
    sg.sa_sigaction = f;
    sigaction(SIGINT, &sg, NULL);
    kill(getpid(), SIGINT);
    
    return 0;
}


