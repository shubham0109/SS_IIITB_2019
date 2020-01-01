#include<stdio.h>
#include<unistd.h>

int main(){
	int hard = link("temp.txt","hardlink.txt"); // return 0 in case of success else -1;
	printf("%d\n",hard);
	return 0;
}

/*
to implement hardlink using command line use
$ln "filename" "linkname"
*/
