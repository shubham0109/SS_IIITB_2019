#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("./execut.obj", "./execut.obj", (char*)NULL);
    return 0;
}

