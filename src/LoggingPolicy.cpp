/**
* @file LoggingPolicy.cpp
*/

#include "../include/LoggingPolicy.hpp"

namespace ClustererBackend
{

LoggingPolicy::LoggingPolicy()
{
    this->finishedFlag = false;
}

void LoggingPolicy::setLoggingQueue(ConcurrentLockingQueue<LoggerBufferEntry>* loggingQueue)
{
    this->concurrentLockingQueue = loggingQueue;
}

void LoggingPolicy::execute()
{
    LoggerBufferEntry currentEntry;
    while (!(this->finishedFlag.load() && this->concurrentLockingQueue->isEmpty()))
    {
        this->concurrentLockingQueue->pop(&currentEntry);
        this->executeHelper(currentEntry);
    }
}

void LoggingPolicy::kill()
{
    this->finishedFlag = true;
}

}