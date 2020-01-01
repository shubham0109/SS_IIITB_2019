# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sched.h>
# include <sys/resource.h>

int main(){
    
    int p = getpriority(PRIO_PROCESS, PRIO_USER);
    printf("Current priority: %d\n", p);
    
    int max_priority = sched_get_priority_max(SCHED_FIFO);
    printf("Max priority: %d\n", max_priority);
    
    int min_priority = sched_get_priority_min(SCHED_FIFO);
    printf("Min priority: %d\n", min_priority);
    
    return 0;
}
