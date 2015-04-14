/**
* @file LoggerSeverityType.hpp
* @brief File in which the SeverityType is defined.
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
* @brief The severity type of a log entry.
* @details The severity type of a log entry. It can be one of the following values
* DEBUG, INFO, WARNING, SEVERE or ERROR.
*/
enum class SeverityType : unsigned char
{
    DEBUG = 0, /**<severity type for the debug entries. */
    INFO, /**<severity type for the information entries. */
    WARNING, /**<severity type for the warning entries. */
    SEVERE, /**<severity type for the severe entries. */
    ERROR  /**<severity type for the error entries. */
};

/**
* @brief Converts the severity type to a string.
* @param severityType The severity type to be converted to a string.
* @return std::string Returns the string representation of the severity type.
*/
std::string severityTypeToString(SeverityType severityType);

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
