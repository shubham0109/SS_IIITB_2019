# include <stdio.h>
# include <unistd.h>

int main(){
  int ret;
  ret = link("file1.txt","myhardlnk");
  return ret;
}
