# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

int main(){
    
    int pid1 = fork();
    int pid2, pid3;
    
    if (pid1 > 0){
        pid2 = fork();
        
        if (pid2 > 0){
            pid3 = fork();
            if (pid3 == 0){
                printf("child3, pid: %d\n", getpid());
            }else{
                printf("parent of child 3, pid: %d\n", getppid());
            }
            printf("child2, pid: %d\n", getpid());
        }else {
            printf("parent of child 2, pid: %d\n", getppid());
        }
        printf("child1, pid: %d\n", getpid());
    }else{
        // wait on the first child
        sleep(10);
        waitpid(pid1, NULL, 0);
        printf("parent of child 1, pid: %d\n", getppid());
    }
    
    
    return 0;
}
