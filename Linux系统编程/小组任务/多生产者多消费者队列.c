//Multi-producer , Multi-consumer Queue

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXSIZE 1024
#define PTHREAD_COUNT 10

struct MPMCQueue {
    int data[MAXSIZE];
    int front;
    int rear;
} typedef MPMCQueue;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

MPMCQueue *MPMCQueueInit(int capacity);
void MPMCQueuePush(MPMCQueue *queue, void *s);
void *MPMCQueuePop(MPMCQueue *queue);
void MPMCQueueDestory(MPMCQueue *);

void producer(void* arg)
{

}

void consumer(void* arg)
{

}

int main()
{
    int i;
    srand(time(NULL));

    pthread_t threads_pid[PTHREAD_COUNT];
    pthread_t threads_cid[PTHREAD_COUNT];

    for(i=0;i<PTHREAD_COUNT;i++){   //循环创建多个线程
        pthread_create(&threads_pid[i], NULL, producer, NULL);
        pthread_create(&threads_cid[i], NULL, consumer, NULL);
    }




    for(i=0;i<PTHREAD_COUNT;i++){
        pthread_join(threads_pid[i], NULL);
        pthread_join(threads_cid[i], NULL);
    }


    return 0;
}