#include <stdio.h>
#include <stdlib.h>
#include "osqueue.h"
#include "threadPool.h"

int count = 0;
void hello1 (void* a)
{
    sleep(1);
   printf("hello1\n");
   count++;
}
void hello2 (void* a)
{
    printf("hello2\n");
    count++;
}


void test_thread_pool_sanity()
{
   int i;
   
   ThreadPool* tp = tpCreate(999999999);
   

   tpInsertTask(tp,hello1,NULL);
    tpInsertTask(tp,hello2,NULL);
    tpInsertTask(tp,hello1,NULL);
    tpInsertTask(tp,hello2,NULL);
    tpInsertTask(tp,hello1,NULL);
   
   tpDestroy(tp,1);
}


int main()
{
   test_thread_pool_sanity();
   printf("%d", count);
   return 0;
}
