#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void f()
{
    static int count = 1;
    printf("Timer expired %d times.\n", count++);
}

int main()
{
    struct itimerval it_val;
    
    signal(SIGALRM, f);
    
    it_val.it_value.tv_sec = 3;
    it_val.it_value.tv_usec = 0;
    
    it_val.it_interval.tv_sec = 1;
    it_val.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_REAL, &it_val, NULL);
    while(1);
    exit(EXIT_SUCCESS);
}

