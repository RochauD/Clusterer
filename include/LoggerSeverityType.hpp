/**
* @file LoggerSeverityType.h
*/

#ifndef _LOGGER_SEVERITY_TYPE_H_
#define _LOGGER_SEVERITY_TYPE_H_

// [C++ header files]
// [standard]
#include <string>
// [external]

// [forward declarations]


/**
* @enum SeverityType
* @brief
* @details Detailed Description missing
*/
enum class SeverityType : unsigned char
{
    DEBUG = 0,
    INFO,
    WARNING,
    SEVERE,
    ERROR
};

std::string severityTypeToString(SeverityType severityType);

#endif
