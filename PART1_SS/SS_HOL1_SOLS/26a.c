#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){
	printf("current program started...\n");
    
    execl("./sum","./sum",(char*)NULL);
  
    return 0;
}
