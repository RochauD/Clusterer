/**
 * @file ConfigurationManager.cpp
 * @brief File in which the ConfigurationManager is implemented.
 */
#include "../include/ConfigurationManager.hpp"

// standard headers
#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{
namespace backend
{

ConfigurationManager::ConfigurationManager()
{
    this->clusteringParams.minPopulationSize = 100;
    this->clusteringParams.maxPopulationSize = 500;
    this->clusteringParams.minIterations = 10000;
    this->clusteringParams.maxIterations = 100000;
    this->clusteringParams.minFitness = 1.4;
    this->clusteringParams.maxFitness = 1.7;
    this->clusteringParams.phaseSwitchFitnessValue = 1.4;
    this->clusteringParams.phaseSwitchIterationValue = 5000;
    this->clusteringParams.threadCount = 4;
}

ConfigurationManager::~ConfigurationManager()
{
}


ClusteringParams ConfigurationManager::getClusteringParams()
{
    return this->clusteringParams;
}

uint64_t ConfigurationManager::getMinPopulationSize()
{
    return this->clusteringParams.minPopulationSize;
}

uint64_t ConfigurationManager::getMaxPopulationSize()
{
    return this->clusteringParams.maxPopulationSize;
}

uint64_t ConfigurationManager::getMinIterationsCount()
{
    return this->clusteringParams.minIterations;
}

uint64_t ConfigurationManager::getMaxIterationsCount()
{
    return this->clusteringParams.maxIterations;
}

double ConfigurationManager::getMinFitness()
{
    return this->clusteringParams.minFitness;
}

double ConfigurationManager::getMaxFitness()
{
    return this->clusteringParams.maxFitness;
}

double ConfigurationManager::getPhaseSwitchFitnessValue()
{
    return this->clusteringParams.phaseSwitchFitnessValue;
}

uint64_t ConfigurationManager::getPhaseSwitchIterationValue()
{
    return this->clusteringParams.phaseSwitchIterationValue;
}

uint32_t ConfigurationManager::getThreadCount()
{
    return this->clusteringParams.threadCount;
}


void ConfigurationManager::setClusteringParams(const ClusteringParams& clusteringParams)
{
    this->clusteringParams = clusteringParams;
}

void ConfigurationManager::setMinPopulationSize(uint64_t minPopulationSize)
{
    this->clusteringParams.minPopulationSize = minPopulationSize;
}

void ConfigurationManager::setMaxPopulationSize(uint64_t maxPopulationSize)
{
    this->clusteringParams.maxPopulationSize = maxPopulationSize;
}

void ConfigurationManager::setMinIterationsCount(uint64_t minIterations)
{
    this->clusteringParams.minIterations = minIterations;
}

void ConfigurationManager::setMaxIterationsCount(uint64_t maxIterations)
{
    this->clusteringParams.maxIterations = maxIterations;
}

void ConfigurationManager::setMinFitness(double minFitness)
{
    this->clusteringParams.minFitness = minFitness;
}

void ConfigurationManager::setMaxFitness(double maxFitness)
{
    this->clusteringParams.maxFitness = maxFitness;
}

void ConfigurationManager::setPhaseSwitchFitnessValue(double phaseSwitchFitnessValue)
{
    this->clusteringParams.phaseSwitchFitnessValue = phaseSwitchFitnessValue;
}

void ConfigurationManager::setPhaseSwitchIterationValue(uint64_t phaseSwitchIterationValue)
{
    this->clusteringParams.phaseSwitchIterationValue = phaseSwitchIterationValue;
}

void ConfigurationManager::setThreadCount(uint32_t threadCount)
{
    this->clusteringParams.threadCount = threadCount;
}


void ConfigurationManager::loadClusteringParams(const std::string& fullPathName)
{
    ConfigurationReaderWriter configReader(fullPathName);
    std::unordered_map<std::string, std::string> parameterMap = configReader.readConfiguration();

    // go through the map and assign our parameters
    std::unordered_map<std::string, std::string>::iterator iter;

    iter = parameterMap.find("minPopulationSize");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.minPopulationSize = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find minPopulationSize value in configuration file.");
        throw std::runtime_error("Error! Could not find minPopulationSize value in configuration file.");
    }

    iter = parameterMap.find("maxPopulationSize");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.maxPopulationSize = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find maxPopulationSize value in configuration file.");
        throw std::runtime_error("Error! Could not find maxPopulationSize value in configuration file.");
    }

    iter = parameterMap.find("minIterations");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.minIterations = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find minIterations value in configuration file.");
        throw std::runtime_error("Error! Could not find minIterations value in configuration file.");
    }

    iter = parameterMap.find("maxIterations");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.maxIterations = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find maxIterations value in configuration file.");
        throw std::runtime_error("Error! Could not find maxIterations value in configuration file.");
    }

    iter = parameterMap.find("minFitness");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.minFitness = std::stod(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find minFitness value in configuration file.");
        throw std::runtime_error("Error! Could not find minFitness value in configuration file.");
    }

    iter = parameterMap.find("maxFitness");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.maxFitness = std::stod(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find maxFitness value in configuration file.");
        throw std::runtime_error("Error! Could not find maxFitness value in configuration file.");
    }

    iter = parameterMap.find("phaseSwitchFitnessValue");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.phaseSwitchFitnessValue = std::stod(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find phaseSwitchFitnessValue value in configuration file.");
        throw std::runtime_error("Error! Could not find phaseSwitchFitnessValue value in configuration file.");
    }

    iter = parameterMap.find("phaseSwitchIterationValue");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.phaseSwitchIterationValue = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find phaseSwitchIterationValue value in configuration file.");
        throw std::runtime_error("Error! Could not find phaseSwitchIterationValue value in configuration file.");
    }

    iter = parameterMap.find("threadCount");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.threadCount = std::stoul(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find threadCount value in configuration file.");
        throw std::runtime_error("Error! Could not find threadCount value in configuration file.");
    }
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Loaded Clustering Params succesfully from the following file. File: ", fullPathName);
}

void ConfigurationManager::saveClusteringParams(const std::string& fullPathName)
{
    std::unordered_map<std::string, std::string> parameterMap;
    parameterMap["minPopulationSize"] = std::to_string(this->clusteringParams.minPopulationSize);
    parameterMap["maxPopulationSize"] = std::to_string(this->clusteringParams.maxPopulationSize);
    parameterMap["minIterations"] = std::to_string(this->clusteringParams.minIterations);
    parameterMap["maxIterations"] = std::to_string(this->clusteringParams.maxIterations);
    parameterMap["minFitness"] = std::to_string(this->clusteringParams.minFitness);
    parameterMap["maxFitness"] = std::to_string(this->clusteringParams.maxFitness);
    parameterMap["phaseSwitchFitnessValue"] = std::to_string(this->clusteringParams.phaseSwitchFitnessValue);
    parameterMap["phaseSwitchIterationValue"] = std::to_string(this->clusteringParams.phaseSwitchIterationValue);
    parameterMap["threadCount"] = std::to_string(this->clusteringParams.threadCount);

    ConfigurationReaderWriter configWriter(fullPathName);
    configWriter.writeConfiguration(parameterMap);
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Saved Clustering Params succesfully to the following file. File: ", fullPathName);
}

}
}
