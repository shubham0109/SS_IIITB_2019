#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sched.h>

int main(){
 
    pid_t p = fork(); 
  
    if (p > 0){   
        printf("parent process: %d\n",getpid());
        exit(0);
    }
    else{
        setsid();
        chdir("/");
        umask(0);
        printf("child process: %d\n",getpid());
        sleep(20);
        return 0;     
    } 
    
    return 0; 
} 
