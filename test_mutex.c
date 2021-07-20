#define _GNU_SOURCE
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "mutex.h"

#define NUM_OF_CORS 4 // Can be passed as command line argument.

int x = 0;
struct Mutex mutex;


void *apllyPlusPlusWithMutex(void* t){
    MutexAcquire(&mutex);
    x++;
    MutexRelease(&mutex);
}

void *apllyPlusPlusWithoutMutex(void* t){
    x++;
}

int main(int argc, char* argv[]) {
    MutexInit(&mutex);
    pthread_t threads[10000];
    pthread_attr_t at;
    cpu_set_t cpuset;
    for (int i = 0; i < 10000; i++) {
        CPU_ZERO(&cpuset);
        CPU_SET(i % NUM_OF_CORS, &cpuset);
        pthread_attr_init(&at);
        pthread_attr_setaffinity_np(&at, sizeof(cpuset), &cpuset);
        if(argc > 1 && atoi(argv[1]) == 1)
            pthread_create(&threads[i], NULL, apllyPlusPlusWithMutex, NULL);
        else
            pthread_create(&threads[i], NULL, apllyPlusPlusWithoutMutex, NULL);
    }
    for (int i = 0; i < NUM_OF_CORS; i++) {
        pthread_join(threads[i], NULL);
    }

    sleep(1);
    printf("X = %d. Expected 10000\n", x);
}