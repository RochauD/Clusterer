/**
* @file LoggerBufferEntry.hpp
* @brief File in which the LoggerBufferEntry is defined.
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
* @brief A entry for the Logger class.
* @details A entry for the logger consisting of the SeverityType, the time stamp of the message and
* the message itself.
*/
class LoggerBufferEntry
{
    public:
        /**
        * @brief Default Constructor for the LoggerBufferEntry.
        */
        LoggerBufferEntry() = default;

        /**
        * @brief Constructor for the LoggerBufferEntry.
        * @param severityType The severity type of the entry.
        * @param logTimePoint The time stamp of the entry.
        * @param logMessage The message of of the entry.
        */
        LoggerBufferEntry(SeverityType severityType, std::chrono::system_clock::time_point logTimePoint, std::string logMessage)
        {
            this->severityType = severityType;
            this->logTimePoint = logTimePoint;
            this->logMessage = logMessage;
        }

        /**
        * @var severityType
        * @brief The severityType of the message.
        * @details The severityType of the message used in the logging policies.
        */
        SeverityType severityType;

        /**
        * @var logTimePoint
        * @brief The time stamp of the logging message.
        * @details The time stamp of the logging entry to be used in the logging policies.
        */
        std::chrono::system_clock::time_point logTimePoint;

        /**
        * @var logMessage
        * @brief The logMessage of the message.
        * @details The logMessage of the entry to be used in the logging policies.
        */
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
