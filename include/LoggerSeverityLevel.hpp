/**
* @file LoggerSeverityLevel.hpp
* @brief File in which the SeverityLevel is defined.
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
* @brief The severity level of a log entry.
* @details The severity level of a log entry. It can be one of the following values
* ALL, INFO, WARNING, SEVERE, ERROR, OFF.
*/
enum class SeverityLevel : unsigned char
{
    ALL = 0, /**<includes the types INFO, WARNING, SEVERE, ERROR, DEBUG */
    INFO, /**<includes the types INFO, WARNING, SEVERE, ERROR */
    WARNING, /**<includes the types SEVERE, WARNING, ERROR */
    SEVERE, /**<includes the types SEVERE, ERROR */
    ERROR, /**<includes the types ERROR */
    OFF /**<includes the non of the severity types */
};

/**
* @brief Converts the severity level to a string.
* @param severityLevel The severity level to be converted to a string.
* @return std::string Returns the string representation of the severity level.
*/
std::string severityLevelToString(const SeverityLevel severityLevel);

/**
* @brief Checks if the severity type matches the severity level.
* @param severityLevel The severity level to be matched against the type.
* @param severityType The severity type to be matched against the level.
* @return bool Returns bool if the severity type is matching the severity level.
*/
bool checkSeverityTypeMatch(const SeverityLevel severityLevel, const SeverityType severityType);

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
