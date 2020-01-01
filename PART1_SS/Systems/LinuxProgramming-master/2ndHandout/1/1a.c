#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void callback_fn(void)
{
	static int count = 1;
	printf("Timer expired %d times.\n", count++);
}

int main(int argc, char const *argv[])
{
	struct itimerval it_val;
	typedef void (* sighandler_t)(int);
	if(signal(SIGALRM, (sighandler_t)callback_fn) == SIG_ERR)
	{
		perror("signal()");
		exit(EXIT_FAILURE);
	}

	// timer will expire intially after 3 second
	it_val.it_value.tv_sec = 3;
	it_val.it_value.tv_usec = 0;
	// and then at interval of 1 second every time
	it_val.it_interval.tv_sec = 1;
	it_val.it_interval.tv_usec = 0;
	if(setitimer(ITIMER_REAL, &it_val, NULL) == -1)
	{
		perror("setitimer()");
		exit(EXIT_FAILURE);
	}
	while(1);
	exit(EXIT_SUCCESS);
}