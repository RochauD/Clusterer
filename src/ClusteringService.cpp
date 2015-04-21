/**
 * @file ClusteringService.cpp
 * @brief implementation of Facade for backend items
 */
#include "../include/ClusteringService.hpp"

// standard headers
#include <thread>
// external headers

// internal headers
#include "../include/GraphReader.hpp"

namespace clusterer
{
namespace backend
{

ClusteringService::ClusteringService()
{

}

ClusteringService::~ClusteringService()
{

}


bool ClusteringService::loadConfiguration(std::string fullPathName)
{
    try
    {
        std::unique_lock<std::mutex> lock(this->serviceMutex);
        this->configurationManager.loadClusteringParams(fullPathName);
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO,"[CLS] Loading of configuration parameters successful");
        return true;
    }
    catch (const std::runtime_error& error)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR,
                                               "[CLS] Loading of configuration parameters failed. Error: ",
                                               error.what());
        return false;
    }
}

bool ClusteringService::saveConfiguration(std::string fullPathName)
{
    try
    {
        std::unique_lock<std::mutex> lock(this->serviceMutex);
        this->configurationManager.saveClusteringParams(fullPathName);
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[CLS] Saving of configuration parameters successful");
        return true;
    }
    catch (const std::runtime_error& error)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR,
                                               "[CLS] Saving of configuration parameters failed. Error: ",
                                               error.what());
        return false;
    }
}

ClusteringParams ClusteringService::getConfigurationParameters()
{
    return this->configurationManager.getClusteringParams();
}

bool ClusteringService::loadGraphTypeVertexPairWeight(std::string fullPathName)
{
    std::unique_lock<std::mutex> lock(this->serviceMutex);
    GraphReader graphReader(&this->graph);
    if (graphReader.readFile(fullPathName))
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO,"[CLS] Loading of graph type vertex pair weight was successful");
        return true;
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "[CLS] Loading of graph type vertex pair weight was failed");
        return false;
    }
}

bool ClusteringService::runAlgorithm(bool restart)
{
    {
        std::unique_lock<std::mutex> lock(this->serviceMutex);
        this->algorithmService.setGraph(&this->graph);
        this->algorithmService.setClusteringParameters(this->configurationManager.getClusteringParams());
        this->algorithmService.setPopulation(&this->population);
        this->algorithmService.setOutQueue(&this->outQueue);
    }
    return this->algorithmService.runAlgorithm();
}

void ClusteringService::stopAlgorithm()
{
    this->algorithmService.stopAlgorithm();
}

void ClusteringService::resumeAlgorithm()
{
    this->algorithmService.resumeAlgorithm();
}

clc::ConcurrentLockingQueue<std::pair<IntegerVectorEncoding, double>>* ClusteringService::getOutQueue()
{
    return &this->outQueue;
}


}
}
