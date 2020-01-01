#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){
    char *arguments[] = {"ls","-Rl",(char*)NULL};
	int value = execvp("ls",arguments);
    //printf("return value of execlv: %d\n",value);
    return 0;
}
