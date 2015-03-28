/**
* @file LoggingPolicy.hpp
*/
#ifndef CLUSTERER_COMMON_LOGGING_POLICY_HPP
#define CLUSTERER_COMMON_LOGGING_POLICY_HPP

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
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
