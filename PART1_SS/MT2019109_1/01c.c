# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

int main(){
	int ret;
	ret = mknod("myfifo", 0666);
	return ret;	
}
