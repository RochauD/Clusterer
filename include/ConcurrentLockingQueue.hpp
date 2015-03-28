/**
* @file ConcurrentLockingQueue.hpp
* @brief Defines the class ConcurrentLockingQueue
*/
#ifndef _CONCURRENT_LOCKING_QUEUE_H_
#define _CONCURRENT_LOCKING_QUEUE_H_

// standard headers
#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>
// external headers

// internal headers


/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
{

/**
* @class ConcurrentLockingQueue
* \brief
* \details Detailed Description missing
* \author Denis Rochau
* \pre
* \copyright Denis Rochau, until license is chosen.
*/
template <class Type>
class ConcurrentLockingQueue
{
    public:
        ConcurrentLockingQueue() = default;

        Type pop();
        void pop(Type& value);
        void pop(Type* value);
        bool popNonWaiting(Type& value);
        bool popNonWaiting(Type* value);
        void push(const Type& value);
        void push(Type&& value);
        bool isEmpty();

        // deleted functions
        ConcurrentLockingQueue(const ConcurrentLockingQueue&) = delete;
        ConcurrentLockingQueue& operator=(const ConcurrentLockingQueue&) = delete;

    protected:
    private:
        std::queue<Type> baseQueue;
        std::mutex queueMutex;
        std::condition_variable queueCV;
};

template <class Type>
Type ConcurrentLockingQueue<Type>::pop()
{
    std::unique_lock<std::mutex> lock(this->queueMutex);
    while (baseQueue.empty())
    {
        queueCV.wait(lock);
    }
    auto value = std::move(baseQueue.front());
    baseQueue.pop();
    return value;
}

template <class Type>
void ConcurrentLockingQueue<Type>::pop(Type& value)
{
    std::unique_lock<std::mutex> lock(this->queueMutex);
    while (baseQueue.empty())
    {
        queueCV.wait(lock);
    }
    value = std::move(baseQueue.front());
    baseQueue.pop();
}

template <class Type>
void ConcurrentLockingQueue<Type>::pop(Type* value)
{
    std::unique_lock<std::mutex> lock(this->queueMutex);
    while (baseQueue.empty())
    {
        queueCV.wait(lock);
    }
    *value = std::move(baseQueue.front());
    baseQueue.pop();
}

template <class Type>
bool ConcurrentLockingQueue<Type>::popNonWaiting(Type& value)
{
    if (std::try_lock(this->queueMutex))
    {
        if (baseQueue.empty())
        {
            this->queueMutex.unlock();
            return false;
        }
        value = std::move(baseQueue.front());
        baseQueue.pop();
        this->queueMutex.unlock();
        return true;
    }
    return false;
}

template <class Type>
bool ConcurrentLockingQueue<Type>::popNonWaiting(Type* value)
{
    if (std::try_lock(this->queueMutex))
    {
        if (baseQueue.empty())
        {
            this->queueMutex.unlock();
            return false;
        }
        *value = std::move(baseQueue.front());
        baseQueue.pop();
        this->queueMutex.unlock();
        return true;
    }
    return false;
}

template <class Type>
void ConcurrentLockingQueue<Type>::push(const Type& value)
{
    {
        std::lock_guard<std::mutex> lock(this->queueMutex);
        baseQueue.push(value);
    }
    queueCV.notify_one();
}

template <class Type>
void ConcurrentLockingQueue<Type>::push(Type&& value)
{
    {
        std::lock_guard<std::mutex> lock(this->queueMutex);
        baseQueue.push(std::move(value));
    }
    queueCV.notify_one();
}

template <class Type>
bool ConcurrentLockingQueue<Type>::isEmpty()
{
    std::lock_guard<std::mutex> lock(this->queueMutex);
    return this->baseQueue.empty();
}

}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
