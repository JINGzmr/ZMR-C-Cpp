#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "common.h"

void Producer()
{
    for (int i = 1; i <= 10; ++i)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // 如果缓冲区已满，则等待消费者消费
        cv_producer.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;

        lock.unlock();
        cv_consumer.notify_one();  // 通知消费者可以消费了
    }
}