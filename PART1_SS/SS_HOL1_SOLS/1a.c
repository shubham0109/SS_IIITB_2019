#include<stdio.h>
#include<unistd.h>

int main(){
	int soft = symlink("temp.txt","softlink.txt"); // return 0 in case of success else -1;
    printf("%d\n",soft);
	return 0;
}	

/*
to implement softlink using command line use
$ln -l "filename" "linkname"
*/
