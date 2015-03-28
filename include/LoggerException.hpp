/**
* @file LoggerException.hpp
*/
#ifndef _LOGGER_EXCEPTION_H_
#define _LOGGER_EXCEPTION_H_

// standard headers
#include <stdexcept>
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
* @class LoggerException
* @brief
* @details Detailed Description missing
*/
class LoggerException : public std::runtime_error
{
    public:
        LoggerException() : std::runtime_error("LoggerException") {}
        LoggerException(const char* message) : std::runtime_error(message) {}
        LoggerException(const std::string& message) : std::runtime_error(message) {}

    protected:
    private:
};

}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
