# include <stdio.h>
# include <unistd.h>

int main(){
    
    char *args[] = {"ls", "-Rl", (char*)NULL};
    execv("/bin/ls", args);
    return 0;
}
