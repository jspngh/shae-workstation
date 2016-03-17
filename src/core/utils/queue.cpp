#include "queue.h"

//template <typename T> T Queue<T>::pop()
QString Queue::pop()
{
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
        cond_.wait(mlock);
    }
    auto val = queue_.front();
    queue_.pop();
    return val;
}

void Queue::pop(QString &item)
{
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
        cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
}

void Queue::push(const QString &item)
{
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
}
