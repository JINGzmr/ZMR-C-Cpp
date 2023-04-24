// Single-producer , single-consumer Queue

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; //  初始化互斥锁🔓（总共一把锁就够了）
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;   //  初始化条件变量

struct SPSCQueue
{
    /* Define Your Data Here */

} typedef SPSCQueue;

SPSCQueue *SPSCQueueInit(int capacity);        // 初始化一个 SPSC 队列，并返回一个指向 SPSCQueue 结构体的指针。capacity: 队列可以存储的元素数量的最大值。
void SPSCQueuePush(SPSCQueue *queue, void *s); // 将一个指向 void 类型的数据指针 s 推入队列中
void *SPSCQueuePop(SPSCQueue *queue);          // 从队列中弹出一个数据指针
void SPSCQueueDestory(SPSCQueue *);            // 销毁一个 SPSC 队列，并释放相关的内存资源

int main()
{

    pthread_t pid, cid; // 定义生产者和消费者的线程ID
    srand(time(NULL));  // 设置随机数生成器的种子，时之后每次获得的随机数更随即

    int ret1 = pthread_create(&pid, NULL, (void*)&SPSCQueuePush, NULL); // 创建生产者线程
    int ret2 = pthread_create(&cid, NULL, (void*)SPSCQueuePop, NULL);   // 创建消费者线程

    //检查线程是否创建成功
    if(ret1!=0){  
        err_thread(ret1, "pthread_create produser error");
    }
    if(ret2!=0){
        err_thread(ret2,"pthead_create consuer error");
    }

    pthread_join(pid, NULL); // 回收生产者线程
    pthread_join(cid, NULL); // 回收消费者线程

    return 0;
}