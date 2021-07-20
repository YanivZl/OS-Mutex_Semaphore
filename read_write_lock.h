#include "mutex.h"

// Implementaion using lecture presantion (Synchronization - slide 47)

struct read_write_lock{
    struct Mutex mutex;
    struct Mutex rw_mutex;
    int read_count;
};

void init_write_read_lock(struct read_write_lock* r_w){
    MutexInit(&r_w->mutex);
    MutexInit(&r_w->rw_mutex);
    r_w->read_count = 0;
}

void read_lock(struct read_write_lock* r_w){
    MutexAcquire(&r_w->mutex);
    r_w->read_count++;
    if(r_w->read_count == 1){
        MutexAcquire(&r_w->rw_mutex);
    }
    MutexRelease(&r_w->mutex);
}

void read_unlock(struct read_write_lock* r_w){
    MutexAcquire(&r_w->mutex);
    r_w->read_count--;
    if(r_w->read_count == 0){
        MutexRelease(&r_w->rw_mutex);    
    }
    MutexRelease(&r_w->mutex);
    
}


void write_lock(struct read_write_lock* r_w){
    MutexAcquire(&r_w->rw_mutex); 
}


void write_unlock(struct read_write_lock* r_w){
    MutexRelease(&r_w->rw_mutex); 
}