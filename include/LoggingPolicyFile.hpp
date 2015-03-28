/**
* @file LoggingPolicyFile.hpp
*/
#ifndef _LOGGING_POLICY_FILE_H_
#define _LOGGING_POLICY_FILE_H_

// standard headers
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>
// external headers

// internal headers
#include "LoggingPolicy.hpp"

/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
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

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
