#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	char buff[80], buff1[80];
	int fd1[2], fd2[2];
	pid_t pid;

	if(pipe(fd1) == -1) ERR_EXIT("pipe()");
	if(pipe(fd2) == -1) ERR_EXIT("pipe()");
	
	if((pid = fork()) == -1) 
	{
		ERR_EXIT("fork()");
	}
	else if(pid > 0) // parent process
	{	
		// Reading message from the child
		// closing the write end of the 1st pipe
		if(close(fd1[1]) == -1) ERR_EXIT("close()");
		// reading from the pipe
		if(read(fd1[0], buff, sizeof(buff)) == -1) ERR_EXIT("read()");
		printf("Message from the child: %s\n", buff);
		// closing the read end of the 1st pipe
		if(close(fd1[0]) == -1) ERR_EXIT("close()");

		// Writing message to the child
		// closing the read end of the second pipe
		if(close(fd2[0]) == -1) ERR_EXIT("close()");
		printf("Enter the message to the Child: ");
		scanf(" %[^\n]", buff1);
		// writing message to the child or second pipe
		write(fd2[1], buff1, sizeof(buff1));// == -1) ERR_EXIT("write()");
		// closing the write end of the second pipe
		close(fd2[1]);// == -1) ERR_EXIT("close()");	
	}
	else // child
	{
		// Write a message from child to parent
		//closing the read end of 1st pipe in child
		if(close(fd1[0]) == -1) ERR_EXIT("close()");
		printf("Enter the message to the Parent: ");
		scanf(" %[^\n]", buff);
		// writing to second pipe
		if(write(fd1[1], buff, sizeof(buff)) == -1) ERR_EXIT("write()");
		// closing the write end of the 1st pipe
		if(close(fd1[1]) == -1) ERR_EXIT("close()");

		// Reading a message from the parent
		// closing the write end of the second pipe
		if(close(fd2[1]) == -1) ERR_EXIT("close()");
		// reading from the second pipe
		if(read(fd2[0], buff1, sizeof(buff1)) == -1) ERR_EXIT("read()");
		printf("Message from parent: %s\n", buff1);
		// closing the read end of the second pipe
		if(close(fd2[0]) == -1) ERR_EXIT("close()");
	}
	exit(EXIT_SUCCESS);
}