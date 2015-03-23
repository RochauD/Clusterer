/**
 * @file ErrorLogger.hpp
 * @brief Logging utility
 */
#ifndef _COMMON_UTILS_ERRORLOGGER_HPP
#define _COMMON_UTILS_ERRORLOGGER_HPP

//Standard libraries
#include <string>
#include <vector>

//Own libraries
#include "compiler_defs.hpp"

namespace common {
namespace utils {

/**
 * @class ErrorLogger
 * @brief logging errors using a singleton logger
 */

class ErrorLogger {
 public:
     /**
      * @brief get logger instance
      * @return ErrorLogger instance
      */
     static ErrorLogger& getInstance() {
         return instance;
     }
     
     /**
      * @brief log assert message
      * @param tag used to identify message source
      * @param msg logged message
      */
     void logAssert(const std::string& tag, const std::string& msg);
    
     
     /**
      * @brief log debug message
      * @param tag used to identify message source
      * @param msg logged message
      */
     void logDebug(const std::string& tag, const std::string& msg);

          
     /**
      * @brief log error message
      * @param tag used to identify message source
      * @param msg logged message
      */
     void logError(const std::string& tag, const std::string& msg);
     
     
     /**
      * @brief log info message
      * @param tag used to identify message source
      * @param msg logged message
      */
     void logInfo(const std::string& tag, const std::string& msg);
     
     
     /**
      * @brief log verbose message
      * @param tag used to identify message source
      * @param msg logged message
      */
     void logVerbose(const std::string& tag, const std::string& msg);


     /**
      * @brief log unexpected errors ("what a terrible failure")
      * @param tag used to identify message source
      * @param msg logged message
      */
     void logWtf(const std::string& tag, const std::string& msg);

 private:
    static ErrorLogger instance;
    DISALLOW_CONSTRUCTION(ErrorLogger);
};

}  // namespace utils
}  // namespace common

#endif  // _COMMON_UTILS_ERRORLOGGER_HPP
