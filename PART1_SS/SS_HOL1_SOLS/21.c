#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

int main(){

    printf("%d\n",getpid());

   	int p = fork();
	if(p == 0)
		printf("child process %d its parent is %d\n",getpid(),getppid());
	else
		printf("parent process %d\n",getpid());

	return 0;
}

