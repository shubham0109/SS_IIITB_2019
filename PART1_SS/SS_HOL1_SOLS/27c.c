#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(){
    
    char *env[] = { (char *)0 };
	execle("/bin/ls","ls","-Rl",(char*)NULL,env);
    return 0;
}
