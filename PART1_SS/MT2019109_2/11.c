#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main()
{
    struct sigaction sg;
    memset(&sg, 0, sizeof(sg));
    
    sg.sa_flags = 0;
    sg.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sg, NULL);
    printf("Ignoring signal SIGINT.\n");
    sleep(5);
    
    printf("\nResetting to default.\n");
    sg.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sg, NULL);
    sleep(5);
    
    exit(EXIT_SUCCESS);
}

