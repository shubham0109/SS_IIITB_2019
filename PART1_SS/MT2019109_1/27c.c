# include <stdio.h>
# include <unistd.h>

int main(){
    
    execle("/bin/ls", "ls", "-Rl", (char*)NULL);
    
    return 0;
}
