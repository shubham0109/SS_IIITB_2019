#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	// array to store two file descriptors
	// pipefd[0] refers to read end of the pipe
	// and pipefd[1] is the write end
	int pipefd[2];
	char buf[30];
	if(pipe(pipefd) == -1) ERR_EXIT("pipe()");
	if(write(pipefd[1], "Hello from the other side!\0", 27) == -1) ERR_EXIT("write()");
	if(read(pipefd[0], buf, sizeof(buf)) == -1) ERR_EXIT("read()");
	printf("Read from Pipe: %s\n", buf);
	exit(EXIT_SUCCESS);
}