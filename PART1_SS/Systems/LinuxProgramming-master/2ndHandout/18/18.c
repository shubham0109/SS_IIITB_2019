#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	int fd1[2], fd2[2];
	pid_t pid;

	if(pipe(fd1) == -1) ERR_EXIT("pipe()");
	if(pipe(fd2) == -1) ERR_EXIT("pipe()");

	if((pid = fork()) == -1) ERR_EXIT("fork()");
	else if(pid > 0)
	{
		// close the read end of the pipe 1
		if(close(fd1[0]) == -1) ERR_EXIT("close()");
		// duplicate write end of pipe 1 to stdout of parent
		if(dup2(fd1[1], STDOUT_FILENO) == -1) ERR_EXIT("dup2()");
		// close read and write end of the 2nd pipe
		if(close(fd2[0]) == -1) ERR_EXIT("close()");
		if(close(fd2[1]) == -1) ERR_EXIT("close()");
		if(execlp("ls", "ls", "-l", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
	}
	else
	{
		if((pid = fork()) == -1) ERR_EXIT("fork()");
		else if(pid > 0)
		{
			if(dup2(fd1[0], STDIN_FILENO) == -1) ERR_EXIT("dup2()");
			if(dup2(fd2[1], STDOUT_FILENO) == -1) ERR_EXIT("dup2()");
			if(close(fd1[1]) == -1) ERR_EXIT("close()");
			if(close(fd2[0]) == -1) ERR_EXIT("close()");
			execlp("grep", "grep", "^d", (char *)NULL);
		}
		else
		{
			if(close(fd2[1]) == -1) ERR_EXIT("close()");
			if(dup2(fd2[0], STDIN_FILENO) == -1) ERR_EXIT("dup2()");
			if(close(fd1[0]) == -1) ERR_EXIT("close()");
			if(close(fd1[1]) == -1) ERR_EXIT("close()");
			execlp("wc", "wc", "-l", (char *)NULL);
		}
	}
}