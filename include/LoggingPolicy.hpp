/**
* @file LoggingPolicy.hpp
*/
#ifndef _LOGGING_POLICY_H_
#define _LOGGING_POLICY_H_

// standard headers
#include <sstream>
#include <memory>
#include <thread>
#include <atomic>
// external headers

// internal headers
#include "LoggerException.hpp"
#include "LoggerBufferEntry.hpp"
#include "LoggerSeverityLevel.hpp"
#include "ConcurrentLockingQueue.hpp"

/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
{

/**
* @class LoggingPolicy
* @brief
* @details Detailed Description missing
*/
class LoggingPolicy
{
    public:
        LoggingPolicy();
        virtual ~LoggingPolicy() {};

        void setLoggingQueue(ConcurrentLockingQueue<LoggerBufferEntry>* loggingQueue);
        void execute();
        void kill();

        // deleted functions
        LoggingPolicy& operator=(const LoggingPolicy&) = delete;
        LoggingPolicy(const LoggingPolicy&) = delete;

    protected:
        virtual void executeHelper(const LoggerBufferEntry& entry) = 0;
        ConcurrentLockingQueue<LoggerBufferEntry>* concurrentLockingQueue;
        std::unique_ptr<std::thread> workerThread;
    private:
        std::atomic<bool> finishedFlag;
};

}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
