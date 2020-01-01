#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* f1()
{
    printf("Thread 1\n");
}

void* f2()
{
    printf("Thread 2\n");
}

void* f3()
{
    printf("Thread 3\n");
}

int main()
{
    pthread_t id1, id2, id3;
    
    pthread_create(&id1, NULL, &f1, NULL);
    pthread_create(&id2, NULL, &f2, NULL);
    pthread_create(&id3, NULL, &f3, NULL);
    
    return 0;
}

