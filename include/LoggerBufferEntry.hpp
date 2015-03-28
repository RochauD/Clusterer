/**
* @file LoggerBufferEntry.hpp
*/
#ifndef CLUSTERER_COMMON_LOGGER_BUFFER_ENTRY_HPP
#define CLUSTERER_COMMON_LOGGER_BUFFER_ENTRY_HPP

// standard headers
#include <string>
#include <chrono>
// external headers

// internal headers
#include "LoggerSeverityType.hpp"
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
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
