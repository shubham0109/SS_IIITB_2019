#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int p1,p2,p3;
    
    p1 = fork();
    
    if(p1 > 0){
        p2 = fork();
        if(p2 > 0 ){
            p3 = fork();                
            if(p3 == 0){
                printf("child p3: %d\n",getpid());
                sleep(20);
            }
            else{
                printf("child p3 parent: %d\n",getppid());
            }            
        }
        else{
            printf("child p2 parent: %d\n",getppid());
        }
        printf("child p1: %d\n",getpid());
        waitpid(p3,NULL,0);
        printf("child p1 parent: %d\n",getppid());
    }
    return 0;
}
