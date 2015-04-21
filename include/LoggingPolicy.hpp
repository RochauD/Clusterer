/**
* @file LoggingPolicy.hpp
* @brief File in which the LoggingPolicy abstract interface is defined.
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
* @brief An abstract interface which implements the correct methods to be used as a policy
* for the logger.
* @details This abstract interface implements all the methods for its subclasses such that those
* can be used as logging policy.
*/
class LoggingPolicy
{
    public:
        /**
        * @brief Constructor for the LoggingPolicy.
        */
        LoggingPolicy();

        /**
        * @brief Virtual destructor for the LoggingPolicy.
        */
        virtual ~LoggingPolicy() {};

        /**
        * @brief Sets logging queue.
        * @details The method sets the logging queue which is used to exchange messages
        * between the worker thread of the logger and the threads which call the logger.
        * @param loggingQueue A pointer to a logging queue.
        * @return void
        */
        void setLoggingQueue(ConcurrentLockingQueue<LoggerBufferEntry>* loggingQueue);

        /**
        * @brief Starts the logging loop.
        * @details The method should pop logging entries of the logging queue and then log
        * them.
        * @return void
        */
        void execute();

        /**
        * @brief Kills the logging loop.
        * @details The method sets the finishedFlag to true and thereby should kill
        * the logging loop.
        * @return void
        */
        void kill();

        // deleted functions
        /**
        * @brief Deleted assignment operator.
        */
        LoggingPolicy& operator=(const LoggingPolicy&) = delete;
        /**
        * @brief Deleted copy constructor.
        */
        LoggingPolicy(const LoggingPolicy&) = delete;

    protected:
        /**
        * @brief Helper function for execute.
        * @details This function is called by the execute method to actual log an entry.
        * @param entry The entry to be logged.
        * @return void
        */
        virtual void executeHelper(const LoggerBufferEntry& entry) = 0;

        /**
        * @var concurrentLockingQueue
        * @brief The messaging queue.
        * @details The LoggerBufferEntry queue which is used to exchange the logging entries
        * between threads.
        */
        ConcurrentLockingQueue<LoggerBufferEntry>* concurrentLockingQueue;
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
