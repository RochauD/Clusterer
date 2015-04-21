/**
* @file GlobalFileLogger.hpp
* @brief File in which the GlobalLogger is defined.
*/
#ifndef CLUSTERER_COMMON_GLOBAL_FILE_LOGGER_HPP
#define CLUSTERER_COMMON_GLOBAL_FILE_LOGGER_HPP

// standard headers
#include <string>
#include <mutex>
#include <atomic>
// external headers

// internal headers
#include "Logger.hpp"
#include "LoggingPolicyFile.hpp"

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
* @class GlobalFileLogger
* @brief A singleton class which uses the Logger class to implement a global file logger.
* @details This class is a Singleton class which uses the class Logger to implement a
* global multithreaded file logger. It uses the logging policy LoggingPolicyFile for the
* logging.
*/
class GlobalFileLogger
{
    public:
        /**
        * @brief Returns a logger instance to log messages.
        * @details This function returns the singleton instance of the logger.
        * @return Logger<LoggingPolicyFile>* A pointer to a logger.
        */
        static Logger<LoggingPolicyFile>* instance();

        /**
        * @brief Initalizes the singleton in case we want to change from the default parameters.
        * @details This function sets the directory and the filename of the log file.
        * @param directory The file path to the logging file directory.
        * @param filename The filename of the logging file without extension.
        * @return void
        * @pre In order to take effect there cannot be a call to instance before init is called.
        * Otherwise this method has no effect unless the logger is reconstructed.
        */
        static void init(const std::string& theDirectory = "./", const std::string& theFilename = "clusterer-log");
    private:
        GlobalFileLogger() {}
        static std::atomic<Logger<LoggingPolicyFile>*> logger;
        static std::mutex mutex;
        static std::string directory;
        static std::string filename;
};

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
