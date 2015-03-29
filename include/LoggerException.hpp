/**
* @file LoggerException.hpp
* @brief File in which the LoggerException is defined.
*/
#ifndef CLUSTERER_COMMON_LOGGER_EXCEPTION_HPP
#define CLUSTERER_COMMON_LOGGER_EXCEPTION_HPP

// standard headers
#include <stdexcept>
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
* @class LoggerException
* @brief The Exception for the Logger and all related classes.
* @details The Exception which should be thrown by all logger policies if something goes wrong.
*/
class LoggerException : public std::runtime_error
{
    public:
        /**
        * @brief Default Constructor for the LoggerException.
        */
        LoggerException() : std::runtime_error("LoggerException") {}

        /**
        * @brief Constructor for the LoggerException.
        * @param message The message for the exceptions.
        */
        LoggerException(const char* message) : std::runtime_error(message) {}

        /**
        * @brief Constructor for the LoggerException.
        * @param message The message for the exceptions.
        */
        LoggerException(const std::string& message) : std::runtime_error(message) {}

    protected:
    private:
};

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
