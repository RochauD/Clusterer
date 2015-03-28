/**
* @file LoggerBufferEntry.hpp
*/
#ifndef _LOGGER_BUFFER_ENTRY_H_
#define _LOGGER_BUFFER_ENTRY_H_

// standard headers
#include <string>
#include <chrono>
// external headers

// internal headers
#include "LoggerSeverityType.hpp"
#include "ConcurrentLockingQueue.hpp"

/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
{

/**
* @class LoggerBufferEntry
* @brief
* @details Detailed Description missing
*/
class LoggerBufferEntry
{
    public:
        LoggerBufferEntry() = default;
        LoggerBufferEntry(SeverityType severityType, std::chrono::system_clock::time_point logTimePoint, std::string logMessage)
        {
            this->severityType = severityType;
            this->logTimePoint = logTimePoint;
            this->logMessage = logMessage;
        }

        SeverityType severityType;
        std::chrono::system_clock::time_point logTimePoint;
        std::string logMessage;
    protected:
    private:
};

}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
