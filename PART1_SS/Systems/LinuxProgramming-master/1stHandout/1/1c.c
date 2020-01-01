#include <sys/types.h> // data types
#include <sys/stat.h> 
#include <stdio.h> // printf()
#include <string.h> // strcmp 
#include <stdlib.h>// exit(), perror()

void show_error(const char* fn_name)
{
	perror(fn_name);
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s (mkfifo | mknod) PIPE_NAME\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/*
	* 777 create sticky bit because it is decimal value not octal
	* 0777 doesn't give appropriate permissions why? due to umask?
	* S_IRWXU | S_IRWXG | S_IRWXO equivalent to 0777 but permissions are given
	* as (0777 & ~umask) umask is by default 0022 can be checked using umask 
	* command so it evaluates to 0755 which is (rwxr-wr-w)
	* (S_IRWXU | S_IRGRP | S_IROTH) evaluate to 0744 and (0744 & ~(0022)) == 0744(rwxr--r--)
	*/
	
	if(strcmp(argv[1], "mkfifo") == 0)
	{
		// create fifo using mkfifo 
		if (mkfifo(argv[2], S_IRWXU | S_IRGRP | S_IROTH))
		{
			show_error("mkfifo()");
		}
	}
	else if(strcmp(argv[1], "mknod") == 0)
	{
		// Create fifo using mknod
		if (mknod(argv[2],
			S_IRWXU | S_IRGRP | S_IROTH | S_IFIFO,
			0/*only used for crating char and block special files*/)
			)
		{
			show_error("mknod()");
		}
	}
	else
	{
		fprintf(stderr, "Usage: %s (mkfifo | mknod) PIPE_NAME\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}