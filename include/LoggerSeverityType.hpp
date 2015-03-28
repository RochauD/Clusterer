/**
* @file LoggerSeverityType.hpp
*/
#ifndef CLUSTERER_COMMON_LOGGER_SEVERITY_TYPE_HPP
#define CLUSTERER_COMMON_LOGGER_SEVERITY_TYPE_HPP

// standard headers
#include <string>
// external headers

// internal headers


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

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
