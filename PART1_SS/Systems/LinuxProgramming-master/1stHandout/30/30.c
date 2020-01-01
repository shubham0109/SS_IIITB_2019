#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

void show_error(char *fn_name)
{
	perror(fn_name);
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	pid_t pid;
	if((pid = fork()) == (pid_t)-1)
		show_error("fork()");
	else if(pid > (pid_t)0)
		exit(EXIT_SUCCESS);
	else
	{
		if(setsid() == (pid_t)-1) show_error("setsid()");
		umask(0);
		// if(chdir("/") == -1) show_error("chdir()");
		// if(close(STDIN_FILENO) == -1) show_error("close()");
		// if(close(STDOUT_FILENO) == -1) show_error("close()");
		// if(close(STDERR_FILENO) == -1) show_error("close()");
		system("bash script.sh");
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}