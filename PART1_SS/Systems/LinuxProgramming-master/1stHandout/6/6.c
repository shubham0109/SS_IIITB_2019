#include <unistd.h> // read write functions ssize_t STDIN_FILENO and STDOUT_FILENO
#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	ssize_t i;
	char buf[120];//max 120 char per line
	i = read(STDIN_FILENO, buf, sizeof(buf)); // stdin = 0
	if(i == (ssize_t)-1)
	{
		perror("read()");
		exit(EXIT_FAILURE);
	} 
	if(write(STDOUT_FILENO, buf, i) == (ssize_t)-1) // stdout = 1
	{
		perror("write()");
		exit(EXIT_FAILURE);
	} 
	exit(EXIT_SUCCESS);
}