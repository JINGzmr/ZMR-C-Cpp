#include <iostream>
#include <pthread.h>
#include <unistd.h>

void* threadPrintHello(void* arg)
{
    while(1)
    {
        sleep(5);
        std::cout << "hello" << std::endl;
    }
}

void* threadPrintWorld(void* arg)
{
    while(1)
    {
        sleep(5);
        std::cout << "world" << std::endl;
    }
} 

int main( int argc , char* argv[])
{
    pthread_t pid_hello , pid_world;

    int ret = 0;

    ret = pthread_create(&pid_hello , NULL , threadPrintHello , NULL);

    if( ret != 0 )
    {
        std::cout << "Create threadHello error" << std::endl;
        return -1;
    }

    ret = pthread_create(&pid_world , NULL , threadPrintWorld , NULL);

    if( ret != 0 )
    {
        std::cout << "Create threadWorld error" << std::endl;
        return -1;
    }

    while(1)
    {
        sleep(10);
        std::cout << "In main thread"  << std::endl;
    }

    pthread_join(pid_hello , NULL);
    pthread_join(pid_world , NULL);

    return 0;
}