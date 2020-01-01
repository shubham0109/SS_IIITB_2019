#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    
    unsigned long long int ini, end;
    rdtscl(ini);
    
    pid_t pid = getpid();
    
    rdtscl(end);
    
    printf("time = %llu ticks", end-ini);
    
    return 0;
}
