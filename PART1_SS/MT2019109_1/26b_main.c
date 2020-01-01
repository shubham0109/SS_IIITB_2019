# include <stdio.h>

int main(int argc, char *argv[]){
    
    if (argc == 2){
        printf("the value entered is: \n");
        printf("%s\n", argv[1]);
    }
    
    return 0;
}
