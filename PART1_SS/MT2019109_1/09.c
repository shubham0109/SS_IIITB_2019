# include <stdio.h>
# include <sys/stat.h>

int main(){
	struct stat s;
	int ret = stat("file_prog7.txt", &s);
	printf("%d\n",ret);
	printf("%d\n",s.st_size);
	printf("%d\n",s.st_gid);
	printf("%d\n",s.st_uid);
	printf("%d\n",s.st_atime);
    printf("%d\n",s.st_dev);
    printf("%d\n",s.st_ino);
    printf("%d\n",s.st_mode);
    printf("%d\n",s.st_nlink);
    printf("%d\n",s.st_uid);
    printf("%d\n",s.st_rdev);
    printf("%d\n",s.st_blocks);
	return 0;
}
