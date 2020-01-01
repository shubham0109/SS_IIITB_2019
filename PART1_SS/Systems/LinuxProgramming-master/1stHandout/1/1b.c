// Program to create hard link
#include <unistd.h> // link()
#include <stdio.h> // printf()
#include <stdlib.h> //exit(), perror(), EXIT_FAILURE, EXIT_SUCCESS

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <path_to_source> <path_to_target>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if(link(argv[1], argv[2]))
	{
		perror("link()");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}