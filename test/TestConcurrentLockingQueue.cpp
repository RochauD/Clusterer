#include "TestConcurrentLockingQueue.hpp"

// standard headers
#include <thread>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>

// local help funcions
void produce(ConcurrentLockingQueue<size_t>* queue, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        queue->push(i);
    }
}

void consume(std::vector<size_t>* resVec, ConcurrentLockingQueue<size_t>* queue, size_t length)
{
    size_t returnValue;
    while (resVec->size() < length)
    {
        queue->pop(returnValue);
        resVec->push_back(returnValue);
    }
}

// testing functions
CPPUNIT_TEST_SUITE_REGISTRATION(TestConcurrentLockingQueue);

void TestConcurrentLockingQueue::setUp(void)
{

}

void TestConcurrentLockingQueue::tearDown(void)
{

}

void TestConcurrentLockingQueue::testIsEmptyReturnsTrueOnEmptyQueue(void)
{
    ConcurrentLockingQueue<size_t> queue;
    CPPUNIT_ASSERT(true == queue.isEmpty());
}

void TestConcurrentLockingQueue::testIsEmptyReturnsFalseOnNonEmptyQueue(void)
{
    ConcurrentLockingQueue<size_t> queue;
    queue.push(1);
    CPPUNIT_ASSERT(false == queue.isEmpty());
}

void TestConcurrentLockingQueue::testPopByReturnValueWorks(void)
{
    ConcurrentLockingQueue<size_t> queue;
    queue.push(1);
    CPPUNIT_ASSERT(1 == queue.pop());
}

void TestConcurrentLockingQueue::testPopByReturnValueWithMoveOnlyObjectWorks(void)
{
    ConcurrentLockingQueue<std::unique_ptr<std::string>> queue;
    std::unique_ptr<std::string> ptr(new std::string("test"));
    queue.push(std::move(ptr));
    auto up = queue.pop();
    CPPUNIT_ASSERT(std::string("test") == *up);
}

void TestConcurrentLockingQueue::testPopByReferenceWorks(void)
{
    ConcurrentLockingQueue<size_t> queue;
    queue.push(1);
    size_t var = 0;
    queue.pop(var);
    CPPUNIT_ASSERT(1 == var);
}

void TestConcurrentLockingQueue::testPopByReferenceWithMoveOnlyObjectWorks(void)
{
    ConcurrentLockingQueue<std::unique_ptr<std::string>> queue;
    std::unique_ptr<std::string> ptr(new std::string("test"));
    queue.push(std::move(ptr));
    queue.pop(ptr);
    CPPUNIT_ASSERT(std::string("test") == *ptr);
}

void TestConcurrentLockingQueue::testPopByPointerWorks(void)
{
    ConcurrentLockingQueue<size_t> queue;
    queue.push(1);
    size_t var = 0;
    queue.pop(&var);
    CPPUNIT_ASSERT(1 == var);
}

void TestConcurrentLockingQueue::testPopByPointerWithMoveOnlyObjectWorks(void)
{
    ConcurrentLockingQueue<std::unique_ptr<std::string>> queue;
    std::unique_ptr<std::string> ptr(new std::string("test"));
    queue.push(std::move(ptr));
    queue.pop(&ptr);
    CPPUNIT_ASSERT(std::string("test") == *ptr);
}

void TestConcurrentLockingQueue::testPopNonWaitingByReferenceWorks(void)
{
    ConcurrentLockingQueue<size_t> queue;
    queue.push(1);
    size_t var = 0;
    CPPUNIT_ASSERT(true == queue.popNonWaiting(var));
    CPPUNIT_ASSERT(1 == var);
}

void TestConcurrentLockingQueue::testPopNonWaitingByReferenceWithMoveOnlyObjectWorks(void)
{
    ConcurrentLockingQueue<std::unique_ptr<std::string>> queue;
    std::unique_ptr<std::string> ptr(new std::string("test"));
    queue.push(std::move(ptr));
    CPPUNIT_ASSERT(true == queue.popNonWaiting(ptr));
    CPPUNIT_ASSERT(std::string("test") == *ptr);
}

void TestConcurrentLockingQueue::testPopNonWaitingByReferenceOnEmptyQueueReturnsFalse(void)
{
    ConcurrentLockingQueue<size_t> queue;
    size_t var = 0;
    CPPUNIT_ASSERT(false == queue.popNonWaiting(var));
    CPPUNIT_ASSERT(0 == var);
}

void TestConcurrentLockingQueue::testPopNonWaitingByPointerWorks(void)
{
    ConcurrentLockingQueue<size_t> queue;
    queue.push(1);
    size_t var = 0;
    CPPUNIT_ASSERT(true == queue.popNonWaiting(&var));
    CPPUNIT_ASSERT(1 == var);
}

void TestConcurrentLockingQueue::testPopNonWaitingByPointerWithMoveOnlyObjectWorks(void)
{
    ConcurrentLockingQueue<std::unique_ptr<std::string>> queue;
    std::unique_ptr<std::string> ptr(new std::string("test"));
    queue.push(std::move(ptr));
    CPPUNIT_ASSERT(true == queue.popNonWaiting(&ptr));
    CPPUNIT_ASSERT(std::string("test") == *ptr);
}

void TestConcurrentLockingQueue::testPopNonWaitingByPointerOnEmptyQueueReturnsFalse(void)
{
    ConcurrentLockingQueue<size_t> queue;
    size_t var = 0;
    CPPUNIT_ASSERT(false == queue.popNonWaiting(&var));
    CPPUNIT_ASSERT(0 == var);
}

void TestConcurrentLockingQueue::testConcurrentLockingQueueExhibitsCorrectBehaviour(void)
{
    const size_t length = 10000;
    std::vector<size_t> resVec;
    ConcurrentLockingQueue<size_t> queue;

    std::thread producer(produce, &queue, length);
    std::thread consumer(consume, &resVec, &queue, length);

    producer.join();
    consumer.join();

    //check size
    CPPUNIT_ASSERT(length == resVec.size());

    // check if all values where added in correct order!
    for (size_t i = 0; i < length; i++)
    {
        CPPUNIT_ASSERT(i == resVec[i]);
    }
}

void TestConcurrentLockingQueue::testConcurrentLockingQueueExhibitsCorrectBehaviourInMultiProducerSetting(void)
{
    const size_t length = 2000;
    const size_t producerThreadCount = 4;
    std::vector<size_t> resVec;
    ConcurrentLockingQueue<size_t> queue;
    size_t expectedVecLength = 0;

    std::vector<std::thread> producerPool;
    for (size_t i = 0; i < producerThreadCount; i++)
    {
        producerPool.push_back(std::thread(produce, &queue, length));
    }

    expectedVecLength = length*producerPool.size();
    std::thread consumer(consume, &resVec, &queue, expectedVecLength);

    for (size_t i = 0; i < producerPool.size(); i++)
    {
        producerPool[i].join();
    }
    consumer.join();

    //check size
    CPPUNIT_ASSERT(expectedVecLength == resVec.size());
    std::sort(resVec.begin(), resVec.end());
    // check if all values are in vector now
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < producerThreadCount; j++)
        {
            CPPUNIT_ASSERT(i == resVec[i*producerThreadCount + j]);
        }
    }
}

void TestConcurrentLockingQueue::testConcurrentLockingQueueExhibitsCorrectBehaviourInMultiConsumerSetting(void)
{
    // careful the result of length/consumerThreadCount needs to be divisible to a whole integer!
    const size_t length = 10000;
    const size_t consumerThreadCount = 4;
    ConcurrentLockingQueue<size_t> queue;
    std::vector<std::vector<size_t>> resVecVec;
    std::vector<size_t> resVec;
    resVecVec.resize(consumerThreadCount);


    std::thread producer(produce, &queue, length);

    std::vector<std::thread> consumerPool;
    for (size_t i = 0; i < consumerThreadCount; i++)
    {
        consumerPool.push_back(std::thread(consume, &resVecVec[i], &queue, length / consumerThreadCount));
    }

    producer.join();
    for (size_t i = 0; i < consumerPool.size(); i++)
    {
        consumerPool[i].join();
    }
    // flatten vectors
    auto startIter = resVecVec.begin();
    auto endIter = resVecVec.end();
    while (startIter != endIter)
    {
        std::back_inserter(resVec) = std::copy(startIter->begin(), startIter->end(), std::back_inserter(resVec));
        ++startIter;
    }
    std::sort(resVec.begin(), resVec.end());
    // check if all values are in vector now
    for (size_t i = 0; i < length; i++)
    {
        CPPUNIT_ASSERT(i == resVec[i]);
    }
}
