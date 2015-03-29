/**
* @file LoggingPolicyFile.hpp
* @brief File in which the LoggingPolicyFile is defined.
*/
#ifndef CLUSTERER_COMMON_LOGGING_POLICY_FILE_HPP
#define CLUSTERER_COMMON_LOGGING_POLICY_FILE_HPP

// standard headers
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>
// external headers

// internal headers
#include "LoggingPolicy.hpp"

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
* @class LoggingPolicyFile
* @brief A logging policy that logs entries to the specified file.
* @details The class LoggingPolicyFile implements a logging policy for the class Logger
* by implementing the abstract interface LoggingPolicy.
*/
class LoggingPolicyFile : public LoggingPolicy
{
    public:
        /**
        * @brief Constructor for the LoggingPolicyFile.
        * @param absoluteFilePath The absolute file path to the logging file.
        */
        LoggingPolicyFile(const std::string& absoluteFilePath);

        /**
        * @brief Constructor for the LoggingPolicyFile.
        * @param pathToFileDir The file path to the logging file directory.
        * @param filename The filename of the logging file.
        */
        LoggingPolicyFile(const std::string& pathToFileDir, const std::string& filename);

        /**
        * @brief Default destructor for the LoggingPolicyFile.
        */
        ~LoggingPolicyFile() = default;

    protected:
        /**
        * @brief Helper function for execute.
        * @details This function is called by the execute method to actual log an entry.
        * @param LoggerBufferEntry The entry to be logged.
        * @return void
        */
        void executeHelper(const LoggerBufferEntry& entry);

        /**
        * @var absoluteFilePath
        * @brief The absolute file path to the logging file.
        */
        std::string absoluteFilePath;
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
