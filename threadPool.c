// shir goldberger 209205798
#include "threadPool.h"

/**
 * print error when system call fail.
 */
void print_error() {
    write(2, ERROR_STRING, strlen(ERROR_STRING));
}

/**
 * execute the tasks in the queue (all the threads).
 * @param tp - the struct of the thread pool.
 * @return nothing.
 */
void *execute(void *tp) {
    ThreadPool *threadPool = (ThreadPool *) tp;
    Task* task;
    while(threadPool->canRunTask) {
        if (pthread_mutex_lock(&(threadPool->mutex)) != 0) {
            print_error();
            tpDestroy(threadPool, 0);
            _exit(EXIT_FAILURE);
        }
        // if the queue is empty and the function tpDestroy didn't activate,
        // wait new task insert to the queue
        if (osIsQueueEmpty(threadPool->tasks) && !threadPool->destroy) {
            int wait = pthread_cond_wait(&(threadPool->cond), &(threadPool->mutex));
            if( wait != 0){
                print_error();
                tpDestroy(threadPool, 0);
                _exit(EXIT_FAILURE);
            }
        }
        // tpDestroy activated - end run tasks
        if (osIsQueueEmpty(threadPool->tasks) && threadPool->destroy) {
            break;
        }
        // do task
        task = (Task *) osDequeue(threadPool->tasks);
        pthread_mutex_unlock(&(threadPool->mutex));
        if (task != NULL) {
            (task->func)(task->args);
            free(task);
        }
    }
    if(pthread_mutex_unlock(&(threadPool->mutex)) != 0){
        print_error();
        tpDestroy(threadPool, 0);
        _exit(EXIT_FAILURE);
    }
    return NULL;
}

/**
 * create a new thread pool.
 * @param numOfThreads - number of threads in the thread pool.
 * @return new thread pool.
 */
ThreadPool *tpCreate(int numOfThreads) {
    if (numOfThreads <= 0) {
        return NULL;
    }
    ThreadPool *threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));
    if (threadPool == NULL) {
        print_error();
        _exit(EXIT_FAILURE);
    }
    threadPool->num_of_threads = numOfThreads;
    threadPool->canRunTask = true;
    threadPool->destroy = false;
    threadPool->tasks = osCreateQueue();
    threadPool->threads = (pthread_t *) malloc(numOfThreads * sizeof(pthread_t));
    if (threadPool->threads == NULL) {
        print_error();
        free(threadPool);
        _exit(EXIT_FAILURE);
    }

    // initialize mutex
    int status = pthread_cond_init(&(threadPool->cond), NULL);
    if (status != 0) {
        print_error();
        _exit(EXIT_FAILURE);
    }
    status = pthread_mutex_init(&threadPool->mutex, NULL);
    if (status != 0) {
        print_error();
        _exit(EXIT_FAILURE);
    }
    // initialize threads
    int i;
    for (i = 0; i < numOfThreads; i++) {
        if (pthread_create(&(threadPool->threads[i]), NULL, execute, threadPool) != 0) {
            tpDestroy(threadPool, 0);
            print_error();
            _exit(EXIT_FAILURE);
        }
    }
    return threadPool;
}

/**
 * free all the variables that allocated.
 * @param threadPool - the struct of the thread pool.
 */
void free_threadPool(ThreadPool *threadPool) {
    if (threadPool->threads != NULL) {
        free(threadPool->threads);
    }
    while(!osIsQueueEmpty(threadPool->tasks)) {
        free(osDequeue(threadPool->tasks));
    }
    osDestroyQueue(threadPool->tasks);
    pthread_mutex_destroy(&threadPool->mutex);
    pthread_cond_destroy(&threadPool->cond);
    free(threadPool);
}

/**
 * destroy the thread pool.
 * @param threadPool - the struct of the thread pool.
 * @param shouldWaitForTasks - 0 if we need to wait just to the tasks that are running now
 * and more than 0 if we need to wait to all the tasks in the queue.
 */
void tpDestroy(ThreadPool *threadPool, int shouldWaitForTasks) {
    if (threadPool == NULL) {
        return;
    }
    // after the task that are running now end, stop the loop of the threads
    if (shouldWaitForTasks == 0) {
        threadPool->canRunTask = false;
    }
    if (!threadPool->destroy) {
        pthread_mutex_lock(&threadPool->mutex);
        threadPool->destroy = true;
        int status1 = pthread_cond_broadcast(&(threadPool->cond));
        int status2 = pthread_mutex_unlock(&(threadPool->mutex));
        if ((status1 != 0) || status2 != 0) {
            // free
            free_threadPool(threadPool);
            return;
        }
        if (threadPool->threads != NULL) {
            int i;
            // wait all the threads end
            for (i = 0; i < threadPool->num_of_threads; i++) {
                if (pthread_join(threadPool->threads[i], NULL) != 0) {
                    print_error();
                    _exit(EXIT_FAILURE);
                }
            }
        }
    }
    // free
    free_threadPool(threadPool);
}

/**
 * insert new task to the queue.
 * @param threadPool - the struct of the thread pool.
 * @param computeFunc - the task we want to execute.
 * @param param - the parameters to the task.
 * @return 0 if the task inserted to the queue and -1 otherwise.
 */
int tpInsertTask(ThreadPool *threadPool, void (*computeFunc)(void *), void *param) {
    // can't inset new task
    if (computeFunc == NULL || threadPool == NULL || threadPool->destroy) {
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
    // lock mutex and check success
    if (pthread_mutex_lock(&threadPool->mutex) != 0) {
        print_error();
        free(t);
        return ERROR;
    }
    // insert the task to the queue
    osEnqueue(threadPool->tasks, (void *) t);
    // wake the thread and check success
    if (pthread_cond_signal(&threadPool->cond) != 0) {
        print_error();
        return ERROR;
    }
    // unlock queue mutex and check success
    if (pthread_mutex_unlock(&threadPool->mutex) != 0) {
        print_error();
        return ERROR;
    }
    return 0;
}