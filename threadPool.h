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
#define ERROR_STRING "Error‬‬ ‫‪in‬‬ ‫‪system‬‬ ‫‪call\n‬‬"

typedef struct thread_pool {
    // tasks queue
    OSQueue *tasks;
    // mutex for tasks queue
    pthread_mutex_t mutex;
    // array of threads
    pthread_t *threads;
    // amount of thread
    int num_of_threads;
    pthread_cond_t cond;
    // true if the function tpDestroy didn't activate
    bool canRunTask;
    // true if the function tpDestroy activated
    bool cannotRunTask;
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
