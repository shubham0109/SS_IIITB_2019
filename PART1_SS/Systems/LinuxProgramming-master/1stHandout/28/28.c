#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int priority;
	if((priority = sched_get_priority_min(SCHED_FIFO)) == -1)
	{
		perror("sched_get_priority_min()");
		exit(EXIT_FAILURE);
	}
	printf("Min priority: %d\n", priority);
	if ((priority = sched_get_priority_max(SCHED_FIFO)) == -1)
	{
		perror("sched_get_priority_max()");
		exit(EXIT_FAILURE);
	}
	printf("Max priority: %d\n", priority);
	exit(EXIT_SUCCESS);
}