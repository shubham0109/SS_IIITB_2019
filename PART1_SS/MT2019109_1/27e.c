# include <stdio.h>
# include <unistd.h>

int main(){
    
    char *args[] = {"ls", "-Rl", (char*)NULL};
    execvp("ls", args);
    
    return 0;
}
