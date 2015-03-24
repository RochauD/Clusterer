#include <iostream>
#include <memory>
#include "include/Logger.hpp"
#include "include/LoggingPolicyFile.hpp"
#include "include/ConfigurationManager.hpp"


int main()
{
    std::unique_ptr<LoggingPolicyFile> uPtr(new LoggingPolicyFile("test.txt"));
    Logger<LoggingPolicyFile> logger(std::move(uPtr), SeverityLevel::ALL);

    for (size_t i = 0; i < 100; i++)
    {
        logger.log(SeverityType::INFO, "Info: ", i);
    }

    logger.log(SeverityType::WARNING, "File: ", __FILE__);


    ConfigurationManager cfg;
    cfg.saveClusteringParams("config1.txt");
    cfg.setMaxFitness(11235467889.000);
    cfg.saveClusteringParams("config2.txt");
    cfg.loadClusteringParams("config2.txt");





    return 0;
}