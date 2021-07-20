#define _GNU_SOURCE
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "counting_semaphore.h"

#define NUM_OF_CORS 4 // Can be passed as command line argument.

int x = 0;
struct Semaphore sem;


void *apllyPlusPlusWithMutex(void* t){
    SemDec(&sem);
    usleep(1);
    x++;
    x++;
    x++;
    x++;
    x++;
    x++;
    x++;
    x++;
    x++;
    x++;
    SemInc(&sem);
}

int main(int argc, char* argv[]) {
    if(argc < 2)
        exit(0);
    SemInit(&sem, atoi(argv[1]));
    pthread_t threads[10000];
    pthread_attr_t at;
    cpu_set_t cpuset;
    for (int i = 0; i < 10000; i++) {
        CPU_ZERO(&cpuset);
        CPU_SET(i % NUM_OF_CORS, &cpuset);
        pthread_attr_init(&at);
        pthread_attr_setaffinity_np(&at, sizeof(cpuset), &cpuset);
        pthread_create(&threads[i], NULL, apllyPlusPlusWithMutex, NULL);
    }

    for (int i = 0; i < NUM_OF_CORS; i++) {
        pthread_join(threads[i], NULL);
    }

    sleep(1);
    printf("X = %d. Expected 100000\n", x);
}