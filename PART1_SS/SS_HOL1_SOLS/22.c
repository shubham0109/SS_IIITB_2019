#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(){
	int fd = open("text.txt",O_CREAT | O_RDWR);
	int p = fork();
	if(p == 0){
		write(fd,"child process\n",15);	
		//printf("child process %d\n",getpid());
	}
	else{
		write(fd,"parent process\n",16);
		//printf("parent process %d\n",getppid());
	}
	return 0;
}

/*
file output is:
parent process
child process
*/
