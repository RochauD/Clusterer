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
 * @class Logger
 * @brief logging errors
 */
template<class LoggingPolicy>
class Logger
{
    public:
        Logger(std::unique_ptr<LoggingPolicy> loggingPolicy, SeverityLevel severityLevel = SeverityLevel::ALL);
        ~Logger();

        template<typename... Types>
        void log(SeverityType severityType, Types... arguments);
        void setSeverityLevel(SeverityLevel severityLevel);
        SeverityLevel getSeverityLevel();

        // deleted functions
        Logger(const Logger&) = delete;
        Logger(const Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;

    private:
        void logHelper();
        template<typename FirstArg, typename...RemainingArgs>
        void logHelper(FirstArg firstArg, RemainingArgs... remainingArgs);


        std::mutex loggerMutex;
        std::unique_ptr<LoggingPolicy> loggingPolicy;
        ConcurrentLockingQueue<LoggerBufferEntry> loggingQueue;
        SeverityLevel severityLevel;

        std::unique_ptr<std::thread> workerThread;

        // class variable with no state
        std::stringstream logBufferStream;
        LoggerBufferEntry newEntry;
};

template<class LoggingPolicy>
Logger<LoggingPolicy>::Logger(std::unique_ptr<LoggingPolicy> loggingPolicy, SeverityLevel severityLevel)
{
    this->loggingPolicy = std::move(loggingPolicy);
    this->severityLevel = severityLevel;
    this->loggingPolicy->setLoggingQueue(&this->loggingQueue);
    this->workerThread = std::unique_ptr<std::thread>(new std::thread(&LoggingPolicy::execute, std::move(this->loggingPolicy.get())));
}

template<class LoggingPolicy>
Logger<LoggingPolicy>::~Logger()
{
    this->loggingPolicy->kill();
    this->workerThread->join();
}

template<class LoggingPolicy>
template<typename... Types>
void Logger<LoggingPolicy>::log(SeverityType severityType, Types... arguments)
{
    std::lock_guard<std::mutex> lock(this->loggerMutex);
    if (checkSeverityTypeMatch(this->severityLevel, severityType))
    {
        this->newEntry.logTimePoint = std::chrono::system_clock::now();
        this->newEntry.severityType = severityType;
        this->logHelper(arguments...);
    }
}

template<class LoggingPolicy>
void Logger<LoggingPolicy>::setSeverityLevel(SeverityLevel severityLevel)
{
    std::lock_guard<std::mutex> lock(this->loggerMutex);
    this->severityLevel = severityLevel;
}

template<class LoggingPolicy>
SeverityLevel Logger<LoggingPolicy>::getSeverityLevel()
{
    std::lock_guard<std::mutex> lock(this->loggerMutex);
    return this->severityLevel;
}


template<class LoggingPolicy>
void Logger<LoggingPolicy>::logHelper()
{
    this->newEntry.logMessage = this->logBufferStream.str();
    this->loggingQueue.push(this->newEntry);
    this->logBufferStream.str(std::string()); // clear bufferStream
}

template<class LoggingPolicy>
template<typename FirstArg, typename...RemainingArgs>
void Logger<LoggingPolicy>::logHelper(FirstArg firstArg, RemainingArgs... remainingArgs)
{
    this->logBufferStream << firstArg;
    this->logHelper(remainingArgs...);
}

#endif
