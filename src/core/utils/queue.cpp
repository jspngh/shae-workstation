#include "queue.h"

T Queue::pop()
{
  std::unique_lock<std::mutex> mlock(mutex_);
  while (queue_.empty())
  {
    cond_.wait(mlock);
  }
  auto val = queue_.front();
  queue_.pop();
  return val;
}

void Queue::pop(T& item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  while (queue_.empty())
  {
    cond_.wait(mlock);
  }
  item = queue_.front();
  queue_.pop();
}

void Queue::push(const T& item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  queue_.push(item);
  mlock.unlock();
  cond_.notify_one();
}
