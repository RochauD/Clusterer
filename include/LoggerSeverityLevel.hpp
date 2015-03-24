/**
* @file LoggerSeverityLevel.hpp
* @brief
*/

#ifndef _LOGGER_SEVERITY_LEVEL_H_
#define _LOGGER_SEVERITY_LEVEL_H_

// [C++ header files]
// [standard]
#include <string>
// [external]
#include "LoggerSeverityType.hpp"
// [forward declarations]

/**
* @enum SeverityLevel
* @brief
* @details Detailed Description missing
*/
enum class SeverityLevel : unsigned char
{
    ALL = 0, // INFO, WARNING, SEVERE, ERROR, DEBUG
    INFO, // INFO, WARNING, SEVERE, ERROR
    WARNING, // SEVERE, WARNING, ERROR
    SEVERE, // SEVERE, ERROR
    ERROR, // ERROR
    OFF // -
};

std::string severityLevelToString(const SeverityLevel severityLevel);

bool checkSeverityTypeMatch(const SeverityLevel severityLevel, const SeverityType severityType);

#endif
