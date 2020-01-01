# include <unistd.h>
# include <stdio.h>

int main(int argc, char *argv[]){
    execl("./executb.obj", "./executb.obj", argv[1], (char*)NULL);
    
    return 0;
}
