#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    printf("Ignoring the SIGINT signal.\n");
    signal(SIGINT, SIG_IGN);
    sleep(5);
    printf("\nResetting to default.\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);
    
    return 0;
}

