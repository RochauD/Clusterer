/**
* @file ConcurrentLockingQueue.hpp
* @brief Defines the class ConcurrentLockingQueue
*/
#ifndef CLUSTERER_COMMON_CONCURRENT_LOCKING_QUEUE_HPP
#define CLUSTERER_COMMON_CONCURRENT_LOCKING_QUEUE_HPP

// standard headers
#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>
// external headers

// internal headers


/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace common
* @brief The namespace common is the namespace for all common components of the project.
*/
namespace common
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
	/**
	 * @brief Default constructor for the ConcurrentLockingQueue.
         */
        ConcurrentLockingQueue() = default;

	/**
	 * @brief Removes the next element in the queue if the queue is not
	 * empty and locks the queue if it is empty.
	 * @return Returns the element just removed.
	 */
        Type pop();
	/**
	 * @brief Removes the next element in the queue if the queue is not
	 * empty and locks the queue if it is empty. The difference from pop() 
	 * being the way popped value is communicated.
	 * @param[out] value Reference to removed element in the queue.
	 */
        void pop(Type& value);
	/**
	 * @brief Removes the next element in the queue if the queue is not
	 * empty and locks the queue if it is empty. The difference from pop() 
	 * being the way popped value is communicated.
	 * @param[out] value Pointer to removed element in the queue.
	 */
        void pop(Type* value);
	/**
	 * @brief If none of the threads are locked and the queue is not empty,
	 * then the element is popped. Else, it returns false and does not wait
	 * for the queue to be expanded.
	 * @param[out] value Reference to next element in the queue.
	 * @return True if all the locks were successfully locked and the queue
	 * was not empty. false otherwise.
	 */
        bool popNonWaiting(Type& value);
	/**
	 * @brief If none of the threads are locked and the queue is not empty,
	 * then the element is popped. Else, it returns false and does not wait
	 * for the queue to be expanded.
	 * @param[out] value Pointer to next element in the queue.
	 * @return True if all the locks were successfully locked and the queue
	 * was not empty. false otherwise.
	 */
        bool popNonWaiting(Type* value);
	/**
	 * @brief Inserts a new element at the end of the queue.
	 * @param value Value to be pushed into queue.
	 */
        void push(Type value)
	/**
	 * @brief Inserts a new element at the end of the queue.
	 * @param value Constant reference to the value to be pushed into queue.
	 */
        void push(const Type& value);
	/**
	 * @brief Inserts a new element at the end of the queue.
	 * @param value rvalue reference to the value to be pushed into queue.
	 */
        void push(Type&& value);
	/**
	 * @brief Checks if the queue is empty.
	 * @return True if the queue is empty, false otherwise.
	 */
        bool isEmpty();
	/**
	 * @brief Disallow copyconstruction.
	 */
        ConcurrentLockingQueue(const ConcurrentLockingQueue&) = delete;
	/**
	 * @brief Disallow assignment.
	 */
        ConcurrentLockingQueue& operator=(const ConcurrentLockingQueue&) = delete;

    protected:
    private:
	/**
	 * @var baseQueue
	 * @brief Underlying queue.
	 * @details Concurrent Locking Queue.
	 */
        std::queue<Type> baseQueue;
	/**
	 * @var queueMutex
	 * @brief Mutex.
	 * @details Mutex will be used for mutual exclusion of thread ownership.
	 */
        std::mutex queueMutex;
	/**
	 * @var queueCV
	 * @brief Condition variable.
	 * @details To be used to block other threads until notification is received.
	 */
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
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif