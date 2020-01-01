# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>


int main(){
    
    int pid = fork();
    
    if (pid > 0){
        // parent process
        printf("in parent\n");
        exit(0);
    }else{
        // child process
        sleep(10);
        printf("in child\n");
    }
    
    return 0;
}
