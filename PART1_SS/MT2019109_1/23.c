# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int main(){
    
    int  pid = fork();
    
    if (pid > 0){
        // parent process
        sleep(50);
        printf("in parent\n");
    }else{
        printf("in child\n");
        exit(0);
    }
    
    return 0;
}
