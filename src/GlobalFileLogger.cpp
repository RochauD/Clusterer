/**
* @file GlobalFileLogger.cpp
*/

#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{
namespace common
{

Logger<LoggingPolicyFile>* GlobalFileLogger::instance()
{
    if (logger.load() == nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (logger.load() == nullptr)
        {
            std::unique_ptr<LoggingPolicyFile> uPtr(new LoggingPolicyFile(directory, filename));
            logger = new Logger<LoggingPolicyFile>(std::move(uPtr), SeverityLevel::ALL);
        }
    }
    return logger;
}

void GlobalFileLogger::init(const std::string& theDirectory, const std::string& theFilename)
{
    directory = theDirectory;
    filename = theFilename;
}

std::atomic<Logger<LoggingPolicyFile>*> GlobalFileLogger::logger = nullptr;
std::mutex GlobalFileLogger::mutex;
std::string GlobalFileLogger::directory = "./";
std::string GlobalFileLogger::filename = "clusterer-log";

}
}
