/**
 * @file Logger.hpp
 * @brief File in which the Singleton Logger is defined
 */
#ifndef _LOGGER_HPP
#define _LOGGER_HPP

// standard headers
#include <sstream>
#include <vector>
#include <mutex>
#include <chrono>
#include <string>
#include <memory>
#include <thread>
// external headers

// internal headers
#include "ConcurrentLockingQueue.hpp"
#include "LoggerBufferEntry.hpp"
#include "LoggerSeverityType.hpp"
#include "LoggerSeverityLevel.hpp"

/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
{

/**
 * @class Logger
 * @brief Logs different kind of messages dependend on the LoggingPolicyType used.
 * @details The class Logger logs different kind of messages to an output defined by the
 * LoggingPolicyType used. The LoggingPolicyType needs to specify certain methods in
 * order to function as an accepted logging policy. The logger is able to log different
 * severity levels and its logging output depends also on the severity level issued.
 * Moreover the log function takes all arguments which have the following operator
 * overloaded: operator<< .
 * @tparam LoggingPolicyType LoggingPolicyType is a type that provides the following:
 *   - a void method with the name setLoggingQueue, which takes the following arguments
 *       1. ConcurrentLockingQueue<LoggerBufferEntry>* a pointer to a
 *          ConcurrentLockingQueue<LoggerBufferEntry> object
 *   - a void method with the name execute with no arguments. This method should start
 *     the logging loop
 *   - a void method with the name kill with no arguments. This method should end
 *     the logging loop
 */
template<class LoggingPolicyType>
class Logger
{
    public:
        /**
        * @brief Constructor for the Logger.
        * @param std::unique_ptr<LoggingPolicyType> A unique pointer to the LoggingPolicyType which is used for logging.
        * @param SeverityLevel The severity level that decides whether or not a message is going to be logged.
        */
        Logger(std::unique_ptr<LoggingPolicyType> loggingPolicy, SeverityLevel severityLevel = SeverityLevel::ALL);

        /**
        * @brief Destructor for the Logger.
        */
        ~Logger();

        /**
        * @brief Logs a log message.
        * @param SeverityType The severity type of the message.
        * @tparam Types A number of arguments of any type that can be converted to a string
        * via an overloaded operator<< .
        * @return void
        */
        template<typename... Types>
        void log(SeverityType severityType, Types... arguments);

        /**
        * @brief Sets the severity level of a log message.
        * @details The method sets the severity level of a log message. The severity level is used to only log
        * certain messages.
        * @param SeverityLevel The severity level of the logger.
        * @return void
        */
        void setSeverityLevel(SeverityLevel severityLevel);

        /**
        * @brief Gets the severity level of a log message.
        * @details The method gets the severity level of a log message. The severity level is used to only log
        * certain messages.
        * @return SeverityLevel Returns the current severity level of the logger.
        */
        SeverityLevel getSeverityLevel();

        // deleted functions
        /**
        * @brief Copy constructor for the Logger class is deleted.
        */
        Logger(const Logger&) = delete;

        /**
        * @brief Assignment constructor for the Logger class is deleted.
        */
        Logger& operator=(const Logger&) = delete;

    private:
        void logHelper();
        template<typename FirstArg, typename...RemainingArgs>
        void logHelper(FirstArg firstArg, RemainingArgs... remainingArgs);

        std::mutex loggerMutex;
        std::unique_ptr<LoggingPolicyType> loggingPolicy;
        ConcurrentLockingQueue<LoggerBufferEntry> loggingQueue;
        SeverityLevel severityLevel;

        std::unique_ptr<std::thread> workerThread;

        // class variable with no state
        std::stringstream logBufferStream;
        LoggerBufferEntry newEntry;
};


template<class LoggingPolicyType>
Logger<LoggingPolicyType>::Logger(std::unique_ptr<LoggingPolicyType> loggingPolicy, SeverityLevel severityLevel)
{
    this->loggingPolicy = std::move(loggingPolicy);
    this->severityLevel = severityLevel;
    this->loggingPolicy->setLoggingQueue(&this->loggingQueue);
    this->workerThread = std::unique_ptr<std::thread>(new std::thread(&LoggingPolicyType::execute,
                         std::move(this->loggingPolicy.get())));
}

template<class LoggingPolicyType>
Logger<LoggingPolicyType>::~Logger()
{
    this->loggingPolicy->kill();
    // add a last message in case the queue is sleeping otherwise it is not logged
    this->log(SeverityType::INFO, "Logger was waiting on empty queue.");
    this->workerThread->join();
}

template<class LoggingPolicyType>
template<typename... Types>
void Logger<LoggingPolicyType>::log(SeverityType severityType, Types... arguments)
{
    std::lock_guard<std::mutex> lock(this->loggerMutex);
    if (checkSeverityTypeMatch(this->severityLevel, severityType))
    {
        this->newEntry.logTimePoint = std::chrono::system_clock::now();
        this->newEntry.severityType = severityType;
        this->logHelper(arguments...);
    }
}

template<class LoggingPolicyType>
void Logger<LoggingPolicyType>::setSeverityLevel(SeverityLevel severityLevel)
{
    std::lock_guard<std::mutex> lock(this->loggerMutex);
    this->severityLevel = severityLevel;
}

template<class LoggingPolicyType>
SeverityLevel Logger<LoggingPolicyType>::getSeverityLevel()
{
    std::lock_guard<std::mutex> lock(this->loggerMutex);
    return this->severityLevel;
}

template<class LoggingPolicyType>
void Logger<LoggingPolicyType>::logHelper()
{
    this->newEntry.logMessage = this->logBufferStream.str();
    this->loggingQueue.push(this->newEntry);
    this->logBufferStream.str(std::string()); // clear bufferStream
}

template<class LoggingPolicyType>
template<typename FirstArg, typename...RemainingArgs>
void Logger<LoggingPolicyType>::logHelper(FirstArg firstArg, RemainingArgs... remainingArgs)
{
    this->logBufferStream << firstArg;
    this->logHelper(remainingArgs...);
}

}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
