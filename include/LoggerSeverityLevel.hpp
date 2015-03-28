/**
* @file LoggerSeverityLevel.hpp
* @brief
*/
#ifndef _LOGGER_SEVERITY_LEVEL_H_
#define _LOGGER_SEVERITY_LEVEL_H_

// standard headers
#include <string>
// external headers

// internal headers
#include "LoggerSeverityType.hpp"

/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
{

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

}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
