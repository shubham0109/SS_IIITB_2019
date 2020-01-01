#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	struct stat buff;
	int fd = open("temp.txt",O_RDONLY);
	fstat(fd,&buff);

	printf("ID:  %ld \n",buff.st_dev);
    printf("Inod:%ld \n",buff.st_ino);
    printf("number of hard links:%ld \n",buff.st_nlink);
    printf("uid:%d \n",buff.st_uid);
    printf("gid:%d \n",buff.st_gid);
    printf("size:%ld \n",buff.st_size);
    printf("block size:%ld \n",buff.st_blksize);
    printf("number of blocks:%ld \n",buff.st_blocks);
    printf("time of last access:%ld \n",buff.st_atime);
    printf("time of last modification:%ld \n",buff.st_mtime);
    printf("time of last change:%ld \n",buff.st_ctime);

	return 0;
}

