# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int main(){
    
    pid_t p = fork();
    
    if (p == 0){
        setsid();
        chdir('/');
        umask(0);
        
        printf("child process\n");
        
        sleep(10);
        execl("/bin/ls", "ls", "-Rl", (char*)NULL);
        
        return 0;
    }else{
        printf("Parent process\n");
        exit(0);
    }
}
