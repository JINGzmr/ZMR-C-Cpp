#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 5;  // 缓冲区大小

extern std::queue<int> buffer;  // 缓冲区
extern std::mutex mtx;  // 互斥量，用于保护缓冲区
extern std::condition_variable cv_producer, cv_consumer;  // 条件变量，用于同步生产者和消费者线程

void Producer();
void Consumer();