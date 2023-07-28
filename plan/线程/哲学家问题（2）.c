/**
 * 每个哲学家先尝试拿起一支筷子
 * 成功后再尝试拿第二支
 * 如果失败，就把之前拿起的那只筷子放下，同时continue结束本次任务，等待下一次再和其他线程抢夺cpu
*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int rice = 100;
pthread_mutex_t ch[5];

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
        sleep(1); //以便其他线程有机会获得 CPU 时间并执行，使大量线程等着，倒计时一结束同时竞争，如果这样程序都ok，那nb
        pthread_mutex_lock(&ch[philosopher_id]);    //先拿起一只筷子
        if(pthread_mutex_trylock(&ch[(philosopher_id+1)%5])!=0){ //==0表示该锁未被上锁（另一支筷子还没人拿），同时锁上
            pthread_mutex_unlock(&ch[philosopher_id]);  //进if语句表示已经锁上了（另一支筷子已经被拿走了），那就把一开始拿的筷子给放了
            continue;// 跳过本次循环，等着抢下次的筷子
        }

        printf("%d号哲学家正在吃%d\n",philosopher_id,rice--);
        sleep(rand()%2); //eat

        pthread_mutex_unlock(&ch[philosopher_id]);
        pthread_mutex_unlock(&ch[(philosopher_id+1)%5]);

        sleep(rand()%3); //休息0-2秒，让其他哲学家能够吃上
    }
}