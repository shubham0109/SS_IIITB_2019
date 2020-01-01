#include <stdio.h>

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <name>\n", argv[0]);
		return -1;
	}
	printf("Hello, %s!\n", argv[1]);
	return 0;
}