// shir goldberger 209205798
#include "threadPool.h"

void print_error() {
    write(2, "Error‬‬ ‫‪in‬‬ ‫‪system‬‬ ‫‪call‬‬", strlen("Error‬‬ ‫‪in‬‬ ‫‪system‬‬ ‫‪call‬‬"));
}

void *execute(void *tp) {
    ThreadPool *threadPool = (ThreadPool *) tp;
    Task* task;
    while(threadPool->canRun) {
        int status = pthread_mutex_lock(&(threadPool->mutex));
        if (status != 0) {
            print_error();
            tpDestroy(threadPool, 0);
            _exit(EXIT_FAILURE);
        }
        if (osIsQueueEmpty(threadPool->tasks) && !threadPool->NotRun) {
            int wait = pthread_cond_wait(&(threadPool->cond), &(threadPool->mutex));
            if( wait != 0){
                print_error();
                tpDestroy(threadPool, 0);
                _exit(EXIT_FAILURE);
            }
        }
        if (osIsQueueEmpty(threadPool->tasks) && threadPool->NotRun && threadPool->canRun) {
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
    int mutexUnlock = pthread_mutex_unlock(&(threadPool->mutex));
    if(mutexUnlock != 0){
        print_error();
        tpDestroy(threadPool, 0);
        _exit(EXIT_FAILURE);
    }
    return NULL;





//    ThreadPool *threadPool = (ThreadPool *) tp;
//    if (threadPool == NULL) {
//        print_error();
//        exit(1);
//    }
//    int status;
//    while (!threadPool->destroy) {
//        // lock the mutex
//        status = pthread_mutex_lock(&threadPool->mutex);
//        if (status != 0) {
//            print_error();
//            tpDestroy(threadPool, 0);
//            _exit(EXIT_FAILURE);
//        }
//        if (!osIsQueueEmpty(threadPool->tasks)) {
//            // run task
//            Task *t = (Task *) osDequeue(threadPool->tasks);
//            if (t == NULL) {
//                continue;
//            }
//            t->func(t->args);
//            free(t);
//        } else {
//            status = pthread_mutex_unlock(&threadPool->mutex);
//            // check success
//            if (status != 0) {
//                print_error();
//                tpDestroy(threadPool, 0);
//                _exit(EXIT_FAILURE);
//            }
//        }
//    }
//    return NULL;
}

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
    threadPool->destroy = false;
    threadPool->NotRun = false;
    threadPool->canRun = true;
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

void tpDestroy(ThreadPool *threadPool, int shouldWaitForTasks) {
    if (threadPool->destroy) {
        return;
    }
    if (shouldWaitForTasks > 0) {
        threadPool->canRun = true;
    } else if (shouldWaitForTasks == 0) {
        threadPool->canRun = false;
    } else {
        return;
    }
    // wait for tasks that run now
    // then, destroy the thread pool
    if (!threadPool->NotRun) {
        pthread_mutex_lock(&threadPool->mutex);
        threadPool->NotRun = true;
        int status1 = pthread_cond_broadcast(&(threadPool->cond));
        int status2 = pthread_mutex_unlock(&(threadPool->mutex));
        if ((status1 != 0) || status2 != 0) {
            // free
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

int tpInsertTask(ThreadPool *threadPool, void (*computeFunc)(void *), void *param) {
    if (computeFunc == NULL || threadPool == NULL || threadPool->NotRun) {
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
    int status = pthread_mutex_lock(&threadPool->mutex);
    // check success
    if (status != 0) {
        print_error();
        free(t);
        return ERROR;
    }
    // insert the task to the queue
    osEnqueue(threadPool->tasks, (void *) t);

    status = pthread_cond_signal(&threadPool->cond);
    // check success
    if (status != 0) {
        print_error();
        return ERROR;
    }
    // unlock queue mutex
    status = pthread_mutex_unlock(&threadPool->mutex);
    // check success
    if (status != 0) {
        print_error();
        return ERROR;
    }
    return 0;
}