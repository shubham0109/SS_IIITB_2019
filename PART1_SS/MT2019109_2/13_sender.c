#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    kill(atoi(argv[1]), SIGSTOP);
    printf("does this?\n");
    
    return 0;
}

