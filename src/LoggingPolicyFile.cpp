/**
* @file LoggingPolicyFile.hpp
*/

#include "../include/LoggingPolicyFile.hpp"

LoggingPolicyFile::LoggingPolicyFile(const std::string& absoluteFilePath)
{
    this->absoluteFilePath = absoluteFilePath;
}

LoggingPolicyFile::LoggingPolicyFile(const std::string& pathToFileDir, const std::string& filename)
    : LoggingPolicyFile(pathToFileDir + filename)
{

}

void LoggingPolicyFile::executeHelper(const LoggerBufferEntry& entry)
{
    std::ofstream outputFileStream(this->absoluteFilePath, std::ios::app);
    outputFileStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try
    {
        std::time_t time = std::chrono::system_clock::to_time_t(entry.logTimePoint);
        std::tm* timeInfo = std::localtime(&time);

        // remove when gcc finally reaches version 5.0 and put_time is implemented!
#ifdef __linux__
        char buffer[255] = {0};
        strftime(buffer, 255, "%d/%m/%Y %H:%M:%S", timeInfo);
        outputFileStream << buffer << " : ";
#else
        outputFileStream << std::put_time(timeInfo, "%d/%m/%Y %H:%M:%S") << " : ";
#endif
        outputFileStream << severityTypeToString(entry.severityType) << " : ";
        outputFileStream << entry.logMessage << "\n";

        outputFileStream.close();
    }
    catch (std::ofstream::failure ex)
    {
        const std::string errorStr = "Logger Exception: Could not log to file. File Exception: " + std::string(ex.what());
        throw LoggerException(errorStr);
    }
}
