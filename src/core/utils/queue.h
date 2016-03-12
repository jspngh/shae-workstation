#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

/*!
 * \brief Class providing an interface for a thread safe queue.
 * The class is a thread safe wrapper around a std::queue which enables multiple threads popping and pushing elements.
 */
template <typename T>
class Queue
{
 public:
   /*!
   * \brief pop an element and return a copy. Pop blocks if queue is empty.
   * \return A copy of the element
   */
    T pop();

    void pop(T& item);

    /*!
     * \brief push pushes an element to the back of the queue. Will never block
     * \param item item to be stored in the queue
     */
    void push(const T& item);

    Queue()=default;
    Queue(const Queue&) = delete;            // disable copying
    Queue& operator=(const Queue&) = delete; // disable assignment

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif
