// 存放消息队列,先入先出
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <mutex>
#include <queue>
#include <string>

// 是一个带有模板参数 T 的类。这使得我们可以在实例化该类时指定具体的数据类型
template <typename T>
class Queue { 
public:
// std::lock_guard 被用来在获取锁的同时创建一个对象，并在该对象的生命周期结束时自动释放锁
    void add(const T& data) {
        std::lock_guard<std::mutex> lock(mutex_);
        container_.push(data);
    }

    T remove() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (container_.empty()) {
            return T();
        }
        T data = container_.front();
        container_.pop();
        return data;
    }

private:
    std::mutex mutex_;
    std::queue<T> container_;
};

#endif