#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

void show_error(char *fn_name)
{
	perror(fn_name);
	exit(EXIT_FAILURE);
}

void print_scheduling_policy_and_priority()
{
  	int sched_policy;
	if((sched_policy = sched_getscheduler(0)) == -1)
		show_error("sched_getscheduler()");
	switch (sched_policy)
	{
		case SCHED_OTHER: 
			printf("SCHED_OTHER or default scheduling policy.\n");		
		  	break;
		case SCHED_FIFO:
			printf("FIFO scheduling policy.\n");		
		  	break;
		case SCHED_RR:		
			printf("SCHED_RR scheduling policy.\n");		
		  	break;
	}
}

 
int main()
{
	printf("Before changing the policy process is using ");
	print_scheduling_policy_and_priority();
	struct sched_param param;
	param.sched_priority = 15;   
	if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
		show_error("sched_setscheduler()");
	printf("After changing the policy process is using ");
	print_scheduling_policy_and_priority();
    exit(EXIT_SUCCESS);
}