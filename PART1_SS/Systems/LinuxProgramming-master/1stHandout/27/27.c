#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <execl | execlp | execle | execv | execvp>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int scs = -1;
	if(strcmp(argv[1], "execl") == 0) scs = 1;
	else if(strcmp(argv[1], "execlp") == 0) scs = 2;
	else if(strcmp(argv[1], "execle") == 0) scs = 3;
	else if(strcmp(argv[1], "execv") == 0) scs = 4;
	else if(strcmp(argv[1], "execvp") == 0) scs = 5;
	
	char* const args[] = {"ls", "-Rl", (char *) NULL};
	switch(scs)
	{
		case 1:
			printf("Executing ls -Rl using execl()\n");
			if(execl("/bin/ls", args[0], args[1], (char *) NULL) == -1)
			{
				perror("execl()");
				exit(EXIT_FAILURE);
			}
			break;
		case 2:
			printf("Executing ls -Rl using execlp()\n");
			if(execlp("/bin/ls", args[0], args[1], (char *) NULL) == -1)
			{
				perror("execlp()");
				exit(EXIT_FAILURE);
			}
			break;
		case 3:
			printf("Executing ls -Rl using execle()\n");
			if(execle("/bin/ls", args[0], args[1], (char *) NULL, (char *) NULL) == -1)
			{
				perror("execle()");
				exit(EXIT_FAILURE);
			}
			break;
		case 4:
			printf("Executing ls -Rl using execv()\n");
			if(execv("/bin/ls", args) == -1)
			{
				perror("execv()");
				exit(EXIT_FAILURE);
			}
			break;
		case 5:
			printf("Executing ls -Rl using execvp()\n");
			if(execvp("/bin/ls", args) == -1)
			{
				perror("execvp()");
				exit(EXIT_FAILURE);
			}
			break;
		default:
			fprintf(stderr, "Usage: %s <execl | execlp | execle | execv | execvp>\n", argv[0]);
			exit(EXIT_FAILURE);
	}
}