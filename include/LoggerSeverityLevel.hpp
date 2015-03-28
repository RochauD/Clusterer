/**
* @file LoggerSeverityLevel.hpp
* @brief
*/
#ifndef CLUSTERER_COMMON_LOGGER_SEVERITY_LEVEL_HPP
#define CLUSTERER_COMMON_LOGGER_SEVERITY_LEVEL_HPP

// standard headers
#include <string>
// external headers

// internal headers
#include "LoggerSeverityType.hpp"

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
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
