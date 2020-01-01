#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	int cur_priority = getpriority(PRIO_PROCESS, 0);
	if(cur_priority == -1)
	{
		perror("getpriority()");
		exit(EXIT_FAILURE);
	}
	printf("Priority of the current process: %d\n", cur_priority);
	// nice can return -1 as legitimate nice value to check if it is not the 
	// error we set errno to some value that is not returned by the nice as 
	// error same case with the getpriority or we can set it to zero
	errno = 0;
	// nice sys call increment the priority of the process by the given value
	if(nice(3) == -1 && errno != 0)
	{
		perror("nice()");
		exit(EXIT_FAILURE);
	}
	cur_priority = getpriority(PRIO_PROCESS, 0);
	if (cur_priority == -1 && errno != 0)
	{
		perror("getpriority()");
		exit(EXIT_FAILURE);
	}
	printf("Priority after nice function call: %d\n", cur_priority);
	// set the priority to the given priority ret 0 on success and
	// -1 on failure
	if(setpriority(PRIO_PROCESS, 0, 11) == -1)
	{
		perror("setpriority()");
		exit(EXIT_FAILURE);
	}
	cur_priority = getpriority(PRIO_PROCESS, 0);
	if (cur_priority == -1 && errno != 0)
	{
		perror("getpriority()");
		exit(EXIT_FAILURE);
	}
	printf("Priority after setpriority function call: %d\n", cur_priority);
	exit(EXIT_SUCCESS);
}