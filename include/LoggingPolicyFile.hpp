/**
* @file LoggingPolicyFile.hpp
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
* @brief
* @details Detailed Description missing
*/
class LoggingPolicyFile : public LoggingPolicy
{
    public:
        LoggingPolicyFile(const std::string& absoluteFilePath);
        LoggingPolicyFile(const std::string& pathToFileDir, const std::string& filename);
        ~LoggingPolicyFile() = default;

    protected:
        void executeHelper(const LoggerBufferEntry& entry);

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
