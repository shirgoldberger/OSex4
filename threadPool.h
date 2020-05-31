// shir goldberger 209205798
#ifndef __THREAD_POOL__
#define __THREAD_POOL__

#include "osqueue.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#define ERROR -1

typedef struct thread_pool {
    // tasks queue
    OSQueue *tasks;
    // mutex for tasks queue
    pthread_mutex_t queue_mutex;
    // array of threads
    pthread_t *threads;
    // amount of thread
    int num_of_threads;
    pthread_mutex_t m;
    // true if the function tpDestroy activated
    bool destroy;
} ThreadPool;

typedef struct {
    // the task in function
    void (*func)(void *);

    // the arguments to the task
    void *args;
} Task;

ThreadPool *tpCreate(int numOfThreads);

void tpDestroy(ThreadPool *threadPool, int shouldWaitForTasks);

int tpInsertTask(ThreadPool *threadPool, void (*computeFunc)(void *), void *param);

#endif
