#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){

	execl("/bin/ls","ls","-Rl",(char*)NULL);
    return 0;
}
