/**
* @file LoggerException.hpp
*/

#ifndef _LOGGER_EXCEPTION_H_
#define _LOGGER_EXCEPTION_H_

// [C++ header files]
// [standard]
#include <stdexcept>
#include <string>
// [external]

// [forward declarations]

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

#endif
