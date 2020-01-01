#include <stdio.h>
#include <unistd.h>

int main(){
	int ret;
	ret = symlink("file1.txt", "mysoftlnk");
	return ret;
}
