#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/resource.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sched.h>

int main(){
    int p = getpriority(PRIO_PROCESS,PRIO_USER);
    printf("Current priority:%d\n",p);

    int fifo_max = sched_get_priority_max(SCHED_FIFO);
    printf("FIFO max_priority:%d\n",fifo_max);
    int fifo_min = sched_get_priority_min(SCHED_FIFO);
    printf("FIFO min_priority:%d\n",fifo_min);
    
    int rr_max = sched_get_priority_max(SCHED_RR);
    printf("RR max_priority:%d\n",rr_max);
    int rr_min = sched_get_priority_min(SCHED_RR);
    printf("RR min_priority:%d\n",rr_min); 
    
    return 0;
}

