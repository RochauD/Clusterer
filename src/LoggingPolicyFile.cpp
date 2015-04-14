/**
* @file LoggingPolicyFile.hpp
*/

// standard headers
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>
// external headers
#include <sstream>
#include <boost/filesystem.hpp>
// internal headers
#include "../include/LoggingPolicyFile.hpp"

namespace clusterer
{
namespace common
{

LoggingPolicyFile::LoggingPolicyFile(const std::string& absoluteFilePath)
{
    this->absoluteFilePath = absoluteFilePath;
}

LoggingPolicyFile::LoggingPolicyFile(const std::string& pathToFileDir, const std::string& filename, const std::string& extension)
{
    std::string timeSuffix;
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* timeInfo = std::localtime(&time);
    // remove when gcc finally reaches version 5.0 and put_time is implemented!
#ifdef __linux__
    char buffer[255] = { 0 };
    strftime(buffer, 255, "%d-%m-%Y_%H-%M-%S", timeInfo);
    timeSuffix = buffer;
#else
    std::stringstream ss;
    ss << std::put_time(timeInfo, "%d-%m-%Y_%H-%M-%S");
    timeSuffix = ss.str();
#endif
    // check if file already exists if it does append a count number to the filename.
    this->absoluteFilePath = pathToFileDir + filename + "_" + timeSuffix;
    size_t coreFilenameLength = this->absoluteFilePath.length();
    this->absoluteFilePath += "." + extension;
    boost::filesystem::path p(this->absoluteFilePath);
    if (boost::filesystem::exists(p))
    {
        size_t counter = 1;
        while (boost::filesystem::exists(p))
        {

            this->absoluteFilePath.erase(coreFilenameLength, this->absoluteFilePath.npos);
            this->absoluteFilePath = this->absoluteFilePath + "(" + std::to_string(counter) + ")";
            this->absoluteFilePath += "." + extension;
            p = this->absoluteFilePath;
            counter++;
        }
    }
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

}
}
