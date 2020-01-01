#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //STDIN_FILENO
#include <sys/select.h>

void show_error(const char *fn_name)
{
        perror(fn_name);
        exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	fd_set rfds;
	struct timeval tv;
	int ret_val;

	// watch stdin to see if it has input
	FD_ZERO(&rfds); //clear the rfds
	FD_SET(STDIN_FILENO, &rfds);

	// wait for 10 secs
	tv.tv_sec = 10; 
	tv.tv_usec = 0;

	int nfds = 1;
	ret_val = select(nfds, &rfds, NULL, NULL, &tv);

	if(ret_val < 0) show_error("select()");
	else if(ret_val) 
	{
		char data[512];
		int i;
		for (i = 0; i < 511; ++i)
		{
			scanf("%c", &data[i]);
			if(data[i] == '\n') break;
		}
		data[i] = '\0';
		printf("Data is available in 10 secs.\n");
		printf("Data: %s\n", data);
	}
	else printf("No data was available in 10 secs.\n");
	exit(EXIT_SUCCESS);
}