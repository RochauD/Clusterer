#include <iostream>
#include <memory>
#include "include/Logger.hpp"
#include "include/LoggingPolicyFile.hpp"


int main()
{
    std::unique_ptr<LoggingPolicyFile> uPtr(new LoggingPolicyFile("test.txt"));
    Logger<LoggingPolicyFile> logger(std::move(uPtr), SeverityLevel::ALL);


    logger.log(SeverityType::WARNING, "File: ", __FILE__, " | Function: ", __FUNCTIONW__);

    return 0;
}