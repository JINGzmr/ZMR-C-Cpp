#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "common.h"

void Consumer()
{
    for (int i = 1; i <= 10; ++i)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // 如果缓冲区为空，则等待生产者生产
        cv_consumer.wait(lock, [] { return !buffer.empty(); });

        int value = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << value << std::endl;

        lock.unlock();
        cv_producer.notify_one();  // 通知生产者可以生产了
    }
}