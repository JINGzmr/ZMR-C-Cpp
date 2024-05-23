#include <iostream>
#include <thread>
#include "common.h"

int main()
{
    std::thread producerThread(Producer);
    std::thread consumerThread(Consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}