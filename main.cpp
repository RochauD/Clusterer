#include <iostream>
#include <memory>
#include "include/Logger.hpp"
#include "include/LoggingPolicyFile.hpp"
#include "include/ConfigurationManager.hpp"
#include "include/GlobalFileLogger.hpp"

using namespace clc;
using namespace clb;

int main()
{

    std::unique_ptr<LoggingPolicyFile> uPtr(new LoggingPolicyFile("./", "test"));
    Logger<LoggingPolicyFile> logger(std::move(uPtr), SeverityLevel::ALL);
    GlobalFileLogger::init();

    for (size_t i = 0; i < 100; i++)
    {
        logger.log(SeverityType::INFO, "Info: ", i);
        GlobalFileLogger::instance()->log(SeverityType::DEBUG, "test", i);
    }




    logger.log(SeverityType::WARNING, "File: ", __FILE__);
    logger.log(SeverityType::WARNING, "Definition Exe Version: ", (CLUSTERER_VERSION));
    logger.log(SeverityType::WARNING, "Definition Exe Version FUll: ", CLUSTERER_VERSION_FULL);

    logger.log(SeverityType::WARNING, "Definition Lib Version: ", CLUSTERER_LIB_VERSION);
    logger.log(SeverityType::WARNING, "Definition Lib Version FUll: ", CLUSTERER_LIB_VERSION_FULL);

    ConfigurationManager cfg;
    cfg.saveClusteringParams("config1.txt");
    cfg.setMaxFitness(11235467889.000);
    cfg.saveClusteringParams("config2.txt");
    cfg.loadClusteringParams("config2.txt");

    return 0;
}