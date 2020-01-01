#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sched.h>

void print(int s){
    if(s == SCHED_OTHER)    
        printf("other real time\n");
    else if(s == SCHED_FIFO)
        printf("fifo\n");
    else if(s == SCHED_RR)
        printf("round robin\n");

}
int main(){
    pid_t p = getpid();
    int s = sched_getscheduler(p);
    //printf("%d %d %d",SCHED_OTHER,SCHED_FIFO,SCHED_RR);
    print(s);
    int status;
    struct sched_param a;
    a.sched_priority = 2;
    status = sched_setscheduler(p,SCHED_FIFO,&a);
    s = sched_getscheduler(p);
    //printf("%d\n",s);
    print(s);
    
    struct sched_param b;
    b.sched_priority = 3;
    status = sched_setscheduler(p,SCHED_RR,&b);
    s = sched_getscheduler(p);
    print(s);    
    return 0;
}
