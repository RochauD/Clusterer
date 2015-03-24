/**
* @file LoggerBufferEntry.hpp
*/

#ifndef _LOGGER_BUFFER_ENTRY_H_
#define _LOGGER_BUFFER_ENTRY_H_

// [C++ header files]
// [standard]
#include <string>
#include <chrono>
// [external]
#include "LoggerSeverityType.hpp"
#include "ConcurrentLockingQueue.hpp"
// [forward declarations]


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



#endif
