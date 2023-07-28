// Single-producer , single-consumer Queue
/**
 * 因为是spsc队列
 * 所以运行结果所打印出的 生产者和消费者 的线程号都是唯一的
 * 
 * 当然，只要多创建几个生产者和消费者的线程，并改消费者里的while循环，那就算是mpmc了
 * 
 * 如果要实现的是父亲放苹果，儿子吃苹果；母亲放橘子，女儿吃橘子的模型的话，
 * 就得用三把锁：一把公共锁，一把父亲儿子共用的，另一把母亲女儿共用的
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
// #include <err_thread.h>

int a = 5;
int b = 5;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //  初始化互斥锁🔓*+3（总共一把锁就够了）
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;   //  初始化条件变量

typedef struct Qnode    // 链表结点
{
    int num;
    struct Qnode *next;
}Qnode,*QueuePtr;

struct SPSCQueue    // 队列的链表结构
{
    QueuePtr front, rear;   // 两个指针，分别指向队头和队尾
} typedef SPSCQueue;


SPSCQueue Q;  //定义一个队列

SPSCQueue *SPSCQueueInit(void);        // 初始化一个 SPSC 队列，并返回一个指向 SPSCQueue 结构体的指针。capacity: 队列可以存储的元素数量的最大值。
void SPSCQueuePush(SPSCQueue *queue, Qnode *s); // 将一个指向 void 类型的数据指针 s 推入队列中
void *SPSCQueuePop(SPSCQueue *queue);          // 从队列中弹出一个数据指针
void SPSCQueueDestory(SPSCQueue *queue);            // 销毁一个 SPSC 队列，并释放相关的内存资源


//生产者
void *produser(void *arg)
{
    while(a)
    {
        pthread_mutex_lock(&mutex);
        printf(" ----%d----- \n",a--);

        QueuePtr s = (QueuePtr)malloc(sizeof(Qnode));
        s->num = rand()%1000+1; //随机产生1-1000的随机数（模拟生产）
        s->next = NULL;
        SPSCQueuePush(&Q, s);   //把该结点搞到队列里面去

        pthread_mutex_unlock(&mutex);   //解锁 互斥量
        pthread_cond_signal(&cond);     // 唤醒阻塞在条件变量cond上的线程

        sleep(rand()%3);    //用于在程序执行过程中产生不同的延迟，最大可能的延迟为2秒


    }
}

//消费者
void *consumer(void *arg)
{
    while(b)
    {
        pthread_mutex_lock(&mutex);     //加锁🔓 互斥量

        if(Q.front==Q.rear)    //队列为空(注意：front指向的是头结点，而头结点没有存放数据，真正有数据且是第一个的是Q.front->next)
        {
            pthread_cond_wait(&cond, &mutex);   //阻塞等待条件变量，解锁，并在返回时重新加锁🔓
        }

        printf(" ----%d----- \n",b--);

        SPSCQueuePop(&Q);

        pthread_mutex_unlock(&mutex);

        sleep(rand()%3);    //把时间交回生产者
    }
}

int main()
{

    pthread_t pid, cid; // 定义生产者和消费者的线程ID
    srand(time(NULL));  // 设置随机数生成器的种子，时之后每次获得的随机数更随即

    SPSCQueueInit();

    int ret1 = pthread_create(&pid, NULL, produser, NULL); // 创建生产者线程
    int ret2 = pthread_create(&cid, NULL, consumer, NULL);   // 创建消费者线程

    // 检查线程是否创建成功
    if (ret1 != 0)
    {
        // err_thread(ret1, "pthread_create produser error");
    }
    if (ret2 != 0)
    {
        // err_thread(ret2, "pthead_create consuer error");
    }

    pthread_join(pid, NULL); // 回收生产者线程
    pthread_join(cid, NULL); // 回收消费者线程

    SPSCQueueDestory(&Q);

    return 0;
}

SPSCQueue *SPSCQueueInit(void)  //容量大小capacity没有用到
{
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(Qnode));
    if(!Q.front){
        perror("SPSCQueueInit()");
    }
    else{
        Q.front->next=NULL;
        return &Q;    
    }
}

void SPSCQueuePush(SPSCQueue *queue, Qnode *s)  //因为我定义了全局变量Q，其实这里传不传队列都无所谓～
{
    queue->rear->next=s;    //尾插法
    queue->rear=s;

    printf("produce data: %d \tpthread_id: %lu\n",s->num, pthread_self());
}

void *SPSCQueuePop(SPSCQueue *queue)
{
    QueuePtr p;
    p=queue->front->next;   // 之后要进行free，先保存一下（front是头结点，没有数据，第一个数据在front->next里面）
    
    queue->front->next = p->next;   
    
    printf("comsume data: %d \tpthread_id: %lu\n",p->num, pthread_self());

    if(queue->rear == p){   //既然队尾指针指向的是要删除的结点p
        queue->rear = queue->front;     //那就让尾指针也指向啥也没有的头结点
    }
    free(p);
}

void SPSCQueueDestory(SPSCQueue *queue)
{
    while(queue->front){
        queue->rear = queue->front->next;   //让队尾指针指向第一个有数据的结点
        free(queue->front); //释放第一个结点（从没有数据的也是第一个的结点开始删除）
        
        //接下来rear不再指向队尾（也没有必要再回到队尾的位置），而是每次来恢复被释放掉的front，使之重新指向队列的最前面
        queue->front = queue->rear; 
    }
}


/**
 * 把队列定义成全局变量，要的时候就直接访问就行了
 * 自己再根据视频搞两个生产者和消费者的函数
 * 要生产和消费时，调用相应的队列函数
 * 在main一开始进行队列的初始化
 * 所有线程回收后，再调用函数进行对队列的销毁
*/

