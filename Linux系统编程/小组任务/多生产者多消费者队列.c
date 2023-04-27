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

MPMCQueue Q;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

MPMCQueue *MPMCQueueInit(void);
void MPMCQueuePush(MPMCQueue *queue, void *s);
void *MPMCQueuePop(MPMCQueue *queue);
void MPMCQueueDestory(MPMCQueue *queue);

void *producer(void* arg)
{
    while(1)
    {
        // while((Q.rear+1)%MAXSIZE==Q.front){
        //     pthread_cond_wait(&cond, &mutex); //满的时候可以阻塞生产者吗？
        // }

        pthread_mutex_lock(&mutex);

        int num = rand()%1000+1;
        MPMCQueuePush(&Q, &num);

        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);  //试试broadcast()

        sleep(rand()%3);
    }
}

void *consumer(void* arg)
{
    while(1)
    {
        while(Q.front==Q.rear){
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_mutex_lock(&mutex);

        MPMCQueuePop(&Q);

        pthread_mutex_unlock(&mutex);

        sleep(rand()%3);
    }
}

int main()
{
    int i;
    srand(time(NULL));

    pthread_t threads_pid[PTHREAD_COUNT];
    pthread_t threads_cid[PTHREAD_COUNT];

    MPMCQueueInit();

    for(i=0;i<PTHREAD_COUNT;i++){   //循环创建多个线程
        pthread_create(&threads_pid[i], NULL, producer, NULL);
        pthread_create(&threads_cid[i], NULL, consumer, NULL);
    }

    for(i=0;i<PTHREAD_COUNT;i++){
        pthread_join(threads_pid[i], NULL);
        pthread_join(threads_cid[i], NULL);
    }

    MPMCQueueDestory(&Q);


    return 0;
}


MPMCQueue *MPMCQueueInit(void)
{
    Q.front=0;
    Q.rear=0;
}


void MPMCQueuePush(MPMCQueue *queue, void *s)
{
    queue->data[queue->rear] = *(int*)s; //  ??

    printf("produce data: %d \tpthread_id: %lu\n",*(int*)s, pthread_self());

    queue->rear=(queue->rear+1)%MAXSIZE;    // rear后移一位
}


void *MPMCQueuePop(MPMCQueue *queue)
{
    int num = queue->data[queue->front];
    
    printf("consume data: %d \tpthread_id: %lu\n",num, pthread_self());

    queue->front = (queue->front+1)%MAXSIZE;    //front后移一位
}


void MPMCQueueDestory(MPMCQueue *queue)
{
    queue->front=0;
    queue->rear=0;
}