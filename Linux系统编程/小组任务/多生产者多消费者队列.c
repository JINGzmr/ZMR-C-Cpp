//Multi-producer , Multi-consumer Queue

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MAXSIZE 1024
#define PTHREAD_COUNT 10

struct MPMCQueue {
    int *data;
    int front;
    int rear;
} typedef MPMCQueue;

// MPMCQueue Q;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t pro_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_cond = PTHREAD_COND_INITIALIZER;

MPMCQueue *MPMCQueueInit(int capacity);
void MPMCQueuePush(MPMCQueue *queue, void *s);
void *MPMCQueuePop(MPMCQueue *queue);
void MPMCQueueDestory(MPMCQueue *queue);

void *producer(void* arg)
{
    MPMCQueue *Q = (MPMCQueue*)arg;

    while(1)
    {
        pthread_mutex_lock(&mutex);

        while((Q->rear+1)%MAXSIZE==Q->front){
            pthread_cond_wait(&pro_cond, &mutex); //满的时候可以阻塞生产者吗？
        }

        //pthread_mutex_lock(&mutex);

        int num = rand()%1000+1;
        MPMCQueuePush(Q, &num);

        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&con_cond);  //试试broadcast()

        sleep(rand()%3);
    }
}

void *consumer(void* arg)
{
    MPMCQueue *Q = (MPMCQueue*)arg;

    while(1)
    {
        pthread_mutex_lock(&mutex);

        while(Q->front==Q->rear){
            pthread_cond_wait(&con_cond, &mutex);
        }

        // pthread_mutex_lock(&mutex);

        MPMCQueuePop(Q);

        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&pro_cond);

        sleep(rand()%3);
    }
}

int main()
{
    int i;
    srand(time(NULL));

    pthread_t threads_pid[PTHREAD_COUNT];
    pthread_t threads_cid[PTHREAD_COUNT];

    MPMCQueue *Q = MPMCQueueInit(MAXSIZE);

    for(i=0;i<PTHREAD_COUNT;i++){   //循环创建多个线程
        pthread_create(&threads_pid[i], NULL, producer, Q);
        pthread_create(&threads_cid[i], NULL, consumer, Q);
    }

    for(i=0;i<PTHREAD_COUNT;i++){
        pthread_join(threads_pid[i], NULL);
        pthread_join(threads_cid[i], NULL);
        pthread_detach(threads_pid[i]);
        pthread_detach(threads_cid[i]);
    }

    MPMCQueueDestory(Q);

    return 0;
}


MPMCQueue *MPMCQueueInit(int capacity)
{
    MPMCQueue *Q = (MPMCQueue*)malloc(sizeof(MPMCQueue));
    Q->data = (int*)malloc(sizeof(int)*capacity);
    Q->front=0;
    Q->rear=0;
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
    //不能先free再赋值为0,因为这样就会访问了已释放的内存
    queue->front=0;
    queue->rear=0;
    free(queue->data);
    free(queue);
}