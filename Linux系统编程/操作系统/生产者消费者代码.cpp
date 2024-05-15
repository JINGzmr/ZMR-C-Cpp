#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 5;  // 缓冲区大小

std::queue<int> buffer;  // 缓冲区
std::mutex mtx;  // 互斥量，用于保护缓冲区
std::condition_variable cv_producer, cv_consumer;  // 条件变量，用于同步生产者和消费者线程

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

int main()
{
    std::thread producerThread(Producer);
    std::thread consumerThread(Consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}