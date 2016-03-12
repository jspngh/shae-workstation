#include "queue.h"

template <typename T> T Queue<T>::pop()
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

template <typename T> void Queue<T>::pop(T& item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  while (queue_.empty())
  {
    cond_.wait(mlock);
  }
  item = queue_.front();
  queue_.pop();
}

template <typename T> void Queue<T>::push(const T& item)
{
  std::unique_lock<std::mutex> mlock(mutex_);
  queue_.push(item);
  mlock.unlock();
  cond_.notify_one();
}
