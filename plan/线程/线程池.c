#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define QUEUE_SIZE 16
#define LOW_WATERMARK 2        // 任务队列低水位线
#define HIGH_WATERMARK 10      // 任务队列高水位线
#define ADD_THREAD_THRESHOLD 3 // 任务队列达到高水位线后，每个线程处理的任务数的平均值

// 任务结构体
typedef struct
{
    void (*func)(void *); // 任务函数指针
    void *arg;            // 任务参数
} Task;

// 任务队列结构体
typedef struct
{
    Task queue[QUEUE_SIZE]; // 任务队列
    int front;              // 队首指针
    int rear;               // 队尾指针
    int size;               // 队列大小
    pthread_mutex_t lock;   // 互斥锁
    pthread_cond_t cond;    // 条件变量
} TaskQueue;

// 线程池结构体
typedef struct
{
    pthread_t threads[THREAD_POOL_SIZE]; // 工作线程
    TaskQueue *queue;                    // 任务队列
    int thread_count;                    // 工作线程数
    int queue_size;                      // 任务队列大小
    int shutdown;                        // 关闭标志
    int working_threads;                 // 正在工作的线程数
} ThreadPool;

// 初始化任务队列
void task_queue_init(TaskQueue *queue)
{
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    pthread_mutex_init(&queue->lock, NULL); // 初始化互斥锁
    pthread_cond_init(&queue->cond, NULL);  // 初始化条件变量
}

// 销毁任务队列
void task_queue_destroy(TaskQueue *queue)
{
    pthread_mutex_destroy(&queue->lock); // 销毁互斥锁
    pthread_cond_destroy(&queue->cond);  // 销毁条件变量
}

// 向任务队列中添加任务
void task_queue_push(TaskQueue *queue, Task task)
{
    pthread_mutex_lock(&queue->lock); // 上锁
    // 等待队列非满
    while (queue->size == QUEUE_SIZE)
    {
        pthread_cond_wait(&queue->cond, &queue->lock); // 等待条件变量
    }
    // 添加任务到队尾
    queue->queue[queue->rear] = task;
    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->size++;
    // 发送信号，唤醒等待中的线程
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->lock); // 解锁
}

// 从任务队列中取出任务
Task task_queue_pop(TaskQueue *queue)
{
    pthread_mutex_lock(&queue->lock); // 上锁
    // 等待队列非空
    while (queue->size == 0)
    {
        pthread_cond_wait(&queue->cond, &queue->lock); // 等待条件变量
    }
    // 取出队首任务
    Task task = queue->queue[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->size--;
    // 发送信号，唤醒等待中的线程
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->lock); // 解锁
    return task;
}

// 工作线程函数
void *worker_thread(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    while (1)
    {
        Task task = task_queue_pop(pool->queue);
        // 执行任务
        task.func(task.arg);
        if (pool->shutdown)
        {
            break;
        }
    } 
    pool->working_threads--;
    pthread_exit(NULL);
}

// 初始化线程池
void thread_pool_init(ThreadPool *pool)
{
    pool->queue = (TaskQueue *)malloc(sizeof(TaskQueue)); // 分配任务队列的内存空间
    task_queue_init(pool->queue);                         // 初始化任务队列
    pool->thread_count = THREAD_POOL_SIZE;                // 工作线程数
    pool->queue_size = QUEUE_SIZE;                        // 任务队列大小
    pool->shutdown = 0;                                   // 关闭标志，初始为 0，表示线程池没有关闭
    pool->working_threads = 0;                            // 正在工作的线程数，初始为 0
    int i;
    for (i = 0; i < pool->thread_count; i++)
    {
        // 创建工作线程，并将线程池作为参数传递给工作线程
        pthread_create(&pool->threads[i], NULL, worker_thread, pool);
        pool->working_threads++; // 增加正在工作的线程数
    }
}

// 销毁线程池
void thread_pool_destroy(ThreadPool *pool)
{
    pool->shutdown = 1;
    while (pool->working_threads > 0)
    {
        pthread_cond_signal(&pool->queue->cond); // 唤醒等待中的线程
    }
    int i;
    for (i = 0; i < pool->thread_count; i++)
    {
        pthread_join(pool->threads[i], NULL);
    }
    task_queue_destroy(pool->queue);
    free(pool->queue);
}

// 向线程池中添加任务
void thread_pool_add_task(ThreadPool *pool, Task task)
{
    // 计算每个线程处理的任务数的平均值
    int avg_tasks_per_thread = pool->queue_size / pool->thread_count;
    // 如果任务队列中的任务数量已经超过了高水位线，且每个线程处理的任务数的平均值小于 ADD_THREAD_THRESHOLD
    if (pool->queue->size > HIGH_WATERMARK && avg_tasks_per_thread < ADD_THREAD_THRESHOLD)
    {
        // 添加新的工作线程
        pthread_t thread;
        pthread_create(&thread, NULL, worker_thread, pool);
        pool->working_threads++;
    }
    // 添加任务到任务队列
    task_queue_push(pool->queue, task);
}

// 测试函数
void print_numbers(void *arg)
{
    int num = *(int *)arg;
    printf("Thread %ld prints number %d\n", pthread_self(), num);
    usleep(100000);
}

int main()
{
    ThreadPool pool;         // 创建线程池实例
    thread_pool_init(&pool); // 初始化线程池
    int i;
    for (i = 0; i < 20; i++)
    {
        int *num = (int *)malloc(sizeof(int));           // 创建存储数字的内存空间
        *num = i;                                        // 将数字赋值给内存空间
        Task task = {.func = print_numbers, .arg = num}; // 创建任务，函数为 print_numbers，参数为数字
        thread_pool_add_task(&pool, task);               // 添加任务到线程池中
    }
    sleep(1);                   // 等待 1 秒，等待任务执行完毕
    thread_pool_destroy(&pool); // 销毁线程池
    return 0;
}