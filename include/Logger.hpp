/**
 * @file Logger.hpp
 * @brief File in which the Singleton Logger is defined
 */
#ifndef _LOGGER_HPP
#define _LOGGER_HPP

// standard headers
#include <string>
#include <vector>
// external headers

// internal headers


namespace common
{
namespace utils
{

/**
 * @class ErrorLogger
 * @brief logging errors using a singleton logger
 */

class Logger
{
public:
    /**
     * @brief get logger instance
     * @return ErrorLogger instance
     */
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }


private:
    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger(const Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
};

}  // namespace utils
}  // namespace common

#endif  // _COMMON_UTILS_ERRORLOGGER_HPP
