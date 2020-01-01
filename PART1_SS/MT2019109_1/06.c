#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

int main(){
	char *buf;
	int read_ret = read(0, buf, sizeof(buf));
	int write_ret = write(1, buf, read_ret);

	printf("read return: %d\n",read_ret);
	printf("write return: %d\n",write_ret);

	return 0;
}
