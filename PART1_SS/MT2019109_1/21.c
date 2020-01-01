# include <stdio.h>
# include <unistd.h>


int main(){
    
    pid_t pid = fork();
    
    printf("parent process pid : %d\n", getpid());
    printf("child process pid : %d\n", pid);
    
    return 0;
}
