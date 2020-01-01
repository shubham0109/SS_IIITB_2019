#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* f1()
{
    printf("Thread1 id: %d\n", pthread_self());
}

void* f2()
{
    printf("Thread2 id: %d\n", pthread_self());
}

void* f3()
{
    printf("Thread3 id: %d\n", pthread_self());
}

int main()
{
    pthread_t id1, id2, id3;
    
    pthread_create(&id1, NULL, &f1, NULL);
    pthread_create(&id2, NULL, &f2, NULL);
    pthread_create(&id3, NULL, &f3, NULL);
    
    return 0;
}


