// Multi-producer , Multi-consumer Queue

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h>

#define MAXSIZE 1024
#define PTHREAD_COUNT 10

struct MPMCQueue
{
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

void *producer(void *arg) // 一共创建了10个线程，每个线程都是执行这些任务
{
    MPMCQueue *Q = (MPMCQueue *)arg;

    while (1) // 10个线程中假设有一个线程抢到了cpu，那他就会执行一遍以下操作，最后释放锁。释放之后，这个线程再次和其他10个线程抢夺cpu
    {
        pthread_mutex_lock(&mutex);

        while ((Q->rear + 1) % MAXSIZE == Q->front)
        {
            pthread_cond_wait(&pro_cond, &mutex); // 满的时候可以阻塞生产者吗？
        }

        // pthread_mutex_lock(&mutex);  // 不能放在这边，因为一个线程抢到访问权限后必须马上锁住🔓，来防止后面的线程也访问该公共资源从而造成不必要的结果

        int num = rand() % 1000 + 1;
        MPMCQueuePush(Q, &num);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&con_cond); // 最好是一次唤醒一个

        sleep(rand() % 3); // 作用是让这个刚执行完操作的线程休息一下（模拟程序执行完一个任务后的缓冲时间），如果一共只有这一个线程，那只能等这缓冲时间过了之后再次调用这个线程（导致效率大大降低）
        // 如果是采用多线程的话，这个线程执行完一遍上面的任务后 释放锁 进入缓冲时间，此时其他的9个线程是时刻准备着的，当这个线程一旦释放锁，他们就会在第一时间抢夺cpu，在最快时间内接着干活（效率大大滴）
        // 这也说明了 在相同的缓冲时间 为什么spsm模型里的打印的速度如此慢，而该代码mpmc一次性打印好多，嘎嘎快
    }
}

void *consumer(void *arg)
{
    MPMCQueue *Q = (MPMCQueue *)arg;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (Q->front == Q->rear)
        {
            pthread_cond_wait(&con_cond, &mutex);
        }

        // pthread_mutex_lock(&mutex);

        Q = (MPMCQueue *)MPMCQueuePop(Q);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&pro_cond);

        sleep(rand() % 3);
    }
}

int main()
{
    int i;
    srand(time(NULL));

    pthread_t threads_pid[PTHREAD_COUNT];
    pthread_t threads_cid[PTHREAD_COUNT];

    MPMCQueue *Q = MPMCQueueInit(MAXSIZE);

    for (i = 0; i < PTHREAD_COUNT; i++)
    { // 循环创建多个线程
        pthread_create(&threads_pid[i], NULL, producer, Q);
        pthread_create(&threads_cid[i], NULL, consumer, Q);
    }

    for (i = 0; i < PTHREAD_COUNT; i++)
    {
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
    MPMCQueue *Q = (MPMCQueue *)malloc(sizeof(MPMCQueue));
    Q->data = (int *)malloc(sizeof(int) * capacity);
    Q->front = 0;
    Q->rear = 0;

    return Q;
}

void MPMCQueuePush(MPMCQueue *queue, void *s)
{
    queue->data[queue->rear] = *(int *)s; //  ??

    printf("produce data: %d \tpthread_id: %lu\n", *(int *)s, pthread_self());

    queue->rear = (queue->rear + 1) % MAXSIZE; // rear后移一位
}

void *MPMCQueuePop(MPMCQueue *queue)
{
    int num = queue->data[queue->front];
 
    printf("consume data: %d \tpthread_id: %lu\n", num, pthread_self());

    queue->front = (queue->front + 1) % MAXSIZE; // front后移一位

    return queue;
}

void MPMCQueueDestory(MPMCQueue *queue)
{
    // 不能先free再赋值为0,因为这样就会访问了已释放的内存
    queue->front = 0;
    queue->rear = 0;
    free(queue->data);
    free(queue);
}