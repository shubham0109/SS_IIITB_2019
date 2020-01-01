#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc,char **argv){
	
    if(argc == 4){    
        execl(argv[1],argv[2],argv[3],(char*)NULL); 
    }
    else if(argc == 3){
        execl(argv[1],argv[2],(char*)NULL); 
    }	
    else{
        printf("invalid number of arguments\n");    
    }
    return 0;
}

/*
this program works for only 
3 or 4 external arguments

input args :./a.out /bin/ls ls -Rl (shows recursively all file for current directory)

*/
