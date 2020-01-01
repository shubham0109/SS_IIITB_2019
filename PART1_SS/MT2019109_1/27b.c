# include <stdio.h>
# include <unistd.h>

int main(){
    
    execlp("ls", "ls", "-Rl", (char*)NULL);
    
    return 0;
}
