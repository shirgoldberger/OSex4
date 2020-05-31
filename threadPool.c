// shir goldberger 209205798
#include "threadPool.h"

void print_error() {
    write(2, ‫‪"Error‬‬ ‫‪in‬‬ ‫‪system‬‬ ‫‪call‬‬", strlen("Error‬‬ ‫‪in‬‬ ‫‪system‬‬ ‫‪call‬‬"));
}

ThreadPool *tpCreate(int numOfThreads) {
    ThreadPool *threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));
    threadPool->num_of_threads = numOfThreads;
    threadPool->destroy = false;
    threadPool->tasks = osCreateQueue();
    threadPool->threads = (pthread_t *) malloc(numOfThreads * sizeof(pthread_t));
    int i;
    for (i = 0; i < numOfThreads; i++) {
        pthread_create(&(threadPool->threads[i]), NULL, NULL, threadPool);

    }
    return threadPool;
}

void tpDestroy(ThreadPool *threadPool, int shouldWaitForTasks) {
    if (threadPool->destroy) {
        return;
    }
    // wait for tasks that run now
    // then, destroy the thread pool
    if (shouldWaitForTasks == 0) {
        int i;
        // wait all the threads end
        for (i = 0; i < threadPool->num_of_threads; i++) {
            if (pthread_join(threadPool->threads[i], NULL) != 0){
                print_error();
                _exit(EXIT_FAILURE);
            }
        }
        // do the tasks in the queue and wait for all tasks done
        // then, destroy the thread pool
    } else if (shouldWaitForTasks > 0) {

    }
}

int tpInsertTask(ThreadPool *threadPool, void (*computeFunc)(void *), void *param) {
    if (threadPool->destroy) {
        return ERROR;
    }
    // create new task
    Task* t = (Task *) malloc(sizeof(Task));
    if (t == NULL) {
        print_error();
        return ERROR;
    }
    t->args = param;
    t->func = computeFunc;
    // lock queue mutex
    int status = pthread_mutex_lock(&threadPool->queue_mutex);
    // check success
    if (!status) {
        print_error();
        return ERROR;
    }
    // insert the task to the queue
    osEnqueue(threadPool->tasks, t);
    // unlock queue mutex
    status = pthread_mutex_unlock(&threadPool->queue_mutex);
    // check success
    if (!status) {
        print_error();
        return ERROR;
    }
}