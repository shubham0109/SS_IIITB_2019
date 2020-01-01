#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	char buff[80];
	int fd[2];
	pid_t pid;
	
	if(pipe(fd) == -1) ERR_EXIT("pipe()");

	if((pid = fork()) == -1) ERR_EXIT("fork()");
	else if(pid > 0) //parent
	{
		//closing the read end of the pipe in parent
		if(close(fd[0]) == -1) ERR_EXIT("close()"); 
		printf("Enter the message to the child: ");
		scanf(" %[^\n]", buff);
		if(write(fd[1], buff, sizeof(buff)) == -1) ERR_EXIT("write()");
		if(close(fd[1]) == -1) ERR_EXIT("close()");
	}
	else //child
	{
		// closing the write end of pipe in the child
		if(close(fd[1]) == -1) ERR_EXIT("close()");
		if(read(fd[0], buff, sizeof(buff)) == -1) ERR_EXIT("read()");
		printf("Message from the parent: %s\n", buff);
		if(close(fd[0]) == -1) ERR_EXIT("close()");
	}
	exit(EXIT_SUCCESS);
}