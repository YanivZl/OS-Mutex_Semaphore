#include "mutex.h"
#include <stdio.h>
// Barz implemtetion of counting seamaphore using binary semaphores (1983).

struct Semaphore{
    int value;
    struct Mutex S1;
    struct Mutex S2;
};


void SemInit(struct Semaphore* sem, int value){
    sem->value = value;
    MutexInit(&sem->S1);
    MutexInit(&sem->S2);
    // if value > 0 -> S2 = Unlock, else S2 = Lock
    if(value < 1){
        struct Mutex* tmp = &sem->S2;
        tmp->lock = LOCKED;
    }
}

void SemInc(struct Semaphore* sem){
    MutexAcquire(&sem->S1);
    sem->value++;
    if(sem->value == 1){    
        MutexRelease(&sem->S2);
    }
    MutexRelease(&sem->S1);
}

void SemDec(struct Semaphore* sem){
    MutexAcquire(&sem->S2);
    MutexAcquire(&sem->S1);
    sem->value--;
    if(sem->value > 0){
        MutexRelease(&sem->S2);
    }
    MutexRelease(&sem->S1);
}

