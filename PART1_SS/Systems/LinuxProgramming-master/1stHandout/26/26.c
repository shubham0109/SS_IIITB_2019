#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <path_to_executeable> <argument>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// image of this program will be relaced by new program
	if(execlp(argv[1], argv[1], argv[2], (char *) NULL) == -1)
	{
		perror("execlp()");
		exit(EXIT_FAILURE);
	}
}