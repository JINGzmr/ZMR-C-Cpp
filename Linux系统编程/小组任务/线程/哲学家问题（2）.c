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
    for(i=0;i<5;i++)
    {
        pthread_mutex_init(&ch[i], NULL);
    }

    pthread_t threads_pid[5];
    for(i=0;i<5;i++)
    {
        pthread_create(&threads_pid[i], NULL, eat, i);
    }

    for(i=0;i<5;i++)
    {
        pthread_join(threads_pid[i], NULL);
    }

    return 0;
}

void *eat(void *arg);