#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void f()
{
    printf("Catched SIGSEGV signal\n");
}

int main()
{
    struct sigaction sg;
    sg.sa_sigaction = f;
    sigaction(SIGSEGV, &sg, NULL);
    kill(getpid(), SIGSEGV);
    
    return 0;
}

