/**
 * 每个哲学家不按照“先拿左边的叉子再拿右边的叉子”的顺序拿叉子
 * 而是“先拿编号小的叉子，再拿编号大的叉子”
 * 如果按照这个规则，对于题目给出的哲学家和叉子的编号
 * 0到3号哲学家都会先拿右边再拿左边，但4号哲学家相反，是先拿右边再拿左边
 * 这样就可以避免死锁的情况发生
 * （编号为顺时针增大，4号哲学家在编号为0和4的筷子之间）
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 使用一个 volatile 类型的变量来记录当前还剩下多少饭，
// 并在主线程中监控这个变量的值。
// 当这个变量的值为 0 时，主线程调用 pthread_cancel() 函数向所有线程发送一个取消信号，让它们退出循环
volatile int rice = 100;
pthread_mutex_t ch[5];

void *eat(void *arg);

int main()
{
    srand(time(NULL));

    int i;
    for (i = 0; i < 5; i++)
    {
        pthread_mutex_init(&ch[i], NULL);
    }

    pthread_t threads_pid[5];
    for (i = 0; i < 5; i++)
    {
        int *philosopher_id = malloc(sizeof(int));
        *philosopher_id = i;
        pthread_create(&threads_pid[i], NULL, eat, philosopher_id);
    }

    // 监控 rice 的值，当其为 0 时结束所有线程
    // but:使用 pthread_cancel() 函数向线程发送取消请求后，线程不会立即终止，而是等待被取消点处的线程处理完毕后才会终止
    // 所以如果去掉所有sleep函数后，终端会在打印出"所有 rice 已经被吃完“后继续对rice--，一段时间后停下
    while (1)
    {
        if (rice == 0)
        {
            printf("所有 rice 已经被吃完！\n");
            for (i = 0; i < 5; i++)
            {
                pthread_cancel(threads_pid[i]);
            }
            break;
        }
    }

    for (i = 0; i < 5; i++)
    {
        pthread_join(threads_pid[i], NULL);
    }

    return 0;
}

void *eat(void *arg)
{
    int philosopher_id = *((int *)arg);
    free(arg);

    while (1)
    {
        if (philosopher_id < (philosopher_id + 1) % 5) // 如果是0-3号哲学家
        {  
            sleep(1);
            pthread_mutex_lock(&ch[philosopher_id]); // 先拿右边的（编号小的）
            pthread_mutex_lock(&ch[(philosopher_id + 1) % 5]);

            printf("%d号哲学家正在吃%d\n", philosopher_id, rice--);
            sleep(rand() % 2); // eat

            pthread_mutex_unlock(&ch[philosopher_id]);
            pthread_mutex_unlock(&ch[(philosopher_id + 1) % 5]);

            sleep(rand() % 3); // 休息0-2秒，让其他哲学家能够吃上
        }
        else // 如果是4号哲学家（假设4号哲学家在编号为0和4的筷子之间）
        {
            sleep(1);
            pthread_mutex_lock(&ch[(philosopher_id + 1) % 5]); // 先拿左边的（编号小的）
            pthread_mutex_lock(&ch[philosopher_id]);

            printf("%d号哲学家正在吃%d\n", philosopher_id, rice--);
            sleep(rand() % 2); // eat
            if (rice == 0)
            {
                break;
            }

            pthread_mutex_unlock(&ch[philosopher_id]);
            pthread_mutex_unlock(&ch[(philosopher_id + 1) % 5]);

            sleep(rand() % 3); // 休息0-2秒，让其他哲学家能够吃上
        }
    }
}