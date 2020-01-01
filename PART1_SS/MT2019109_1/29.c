# include <stdio.h>
# include <unistd.h>
# include <sched.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>

int main(){
    pid_t p = getpid();
    
    int s = sched_getscheduler(p));
    
    if (s == SCHED_FIFO){
        printf("FIFO\n");
    }else if(s == SCHED_RR){
        printf("RR\n");
    }else{
        printf("others\n");
    }
}
