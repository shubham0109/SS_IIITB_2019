#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){
 
    pid_t p = fork(); 
  
    if (p > 0){   
        printf("parent process: %d\n",getpid());     	     
    }
    else{
        printf("child process: %d\n",getpid());
        sleep(20);
        //exit(0);     
    } 
    
    return 0; 
} 

/* 
In this parent will terminate before 
child terminates so
orphan process will be created.
*/
