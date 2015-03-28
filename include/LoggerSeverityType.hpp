/**
* @file LoggerSeverityType.h
*/
#ifndef _LOGGER_SEVERITY_TYPE_H_
#define _LOGGER_SEVERITY_TYPE_H_

// standard headers
#include <string>
// external headers

// internal headers


/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
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

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
