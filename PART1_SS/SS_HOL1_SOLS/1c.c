#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int d = mkfifo("pipe",777); 
    printf("%d\n",d);	
    return 0;
}	

/*
$mkfifo pipename
*/
