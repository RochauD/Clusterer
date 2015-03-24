/**
* @file LoggingPolicyFile.hpp
*/

#ifndef _LOGGING_POLICY_FILE_H_
#define _LOGGING_POLICY_FILE_H_

// [C++ header files]
// [standard]
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>
// [external]
#include "LoggingPolicy.hpp"
// [forward declarations]

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

#endif
