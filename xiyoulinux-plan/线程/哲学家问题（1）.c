/**
 * 抢到cpu后先把整个桌子锁住🔓
 * 然后判读是否左右两只筷子都在
 * ok的话拿起两只筷子，再释放调桌子的全局锁，让别的线程去抢夺，判断两只筷子...
 * 拿起筷子的线程吃饭就行了，吃完再放下两只筷子
*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int rice = 100;
pthread_mutex_t ch[5];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //很重要，将全局锁了之后 再拿筷子，避免五个中哲学家同时拿起一支筷子，导致死锁 （去掉sleep和该行代码 可以直观感受）

void *eat(void *arg);

int main()
{
    srand(time(NULL));

    int i;
    for(i=0;i<5;i++){
        pthread_mutex_init(&ch[i],NULL);
    }

    pthread_t threads_pid[5];
    for(i=0;i<5;i++){
        int *philosopher_id = malloc(sizeof(int));
        *philosopher_id = i;
        pthread_create(&threads_pid[i], NULL, eat, philosopher_id);
    }

    for(i=0;i<5;i++){
        pthread_join(threads_pid[i], NULL);
    }

    return 0;
}

void *eat(void *arg)
{
    int philosopher_id = *((int*) arg);
    free(arg);

    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&ch[philosopher_id]);
        pthread_mutex_lock(&ch[(philosopher_id+1)%5]);

        pthread_mutex_unlock(&mutex);

        printf("%d号哲学家正在吃%d\n",philosopher_id,rice--);
        sleep(rand()%2); //eat

        pthread_mutex_unlock(&ch[philosopher_id]);
        pthread_mutex_unlock(&ch[(philosopher_id+1)%5]);

        sleep(rand()%3); //休息0-2秒，让其他哲学家能够吃上
    }


}