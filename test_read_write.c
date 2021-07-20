#define _GNU_SOURCE 1
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "read_write_lock.h"

/*
This program provides a possible solution for first readers writers problem using mutex and semaphore.
I have used 10 readers and 5 producers to demonstrate the solution. You can always play with these values.
*/

#define NUM_OF_CORS 4

struct read_write_lock rw;
pthread_mutex_t mutex;
int cnt = 1;

void *writer(void *wno)
{   
    write_lock(&rw);
    cnt = cnt*2;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt);
    write_unlock(&rw);
}
void *reader(void *rno)
{   
    read_lock(&rw);
    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt);
    read_unlock(&rw);
}

int main()
{   

    pthread_t threads[15];
    init_write_read_lock(&rw);
    cpu_set_t cpuset;
    int a[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //Just used for numbering the reader and writer

    for(int i = 0; i < 15; i++) {
        CPU_ZERO(&cpuset);
        CPU_SET(i % NUM_OF_CORS, &cpuset);
        if(i % 3 == 0)
            pthread_create(&threads[i], NULL, (void *)writer, (void *)&a[i]);
        else
            pthread_create(&threads[i], NULL, (void *)reader, (void *)&a[i]);
    }

    for(int i = 0; i < 15; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
    
}