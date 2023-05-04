#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int rice = 100;
pthread_mutex_t ch[5];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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