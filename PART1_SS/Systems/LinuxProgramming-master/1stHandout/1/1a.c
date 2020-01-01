// Program to create soft link
#include <stdio.h> //fprintf() perror()
#include <unistd.h> //symlink function
#include <stdlib.h> //exit() EXIT_FAILURE

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <path_to_source> <path_to_target>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if(symlink(argv[1], argv[2])) 
	{
		perror("symlink()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}