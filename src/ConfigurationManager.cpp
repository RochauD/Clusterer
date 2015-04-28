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
    this->clusteringParams.uniquePopulationSelection = true;
    this->clusteringParams.reevaluateUniquePopulation = true;
    this->clusteringParams.maxMinDensityClusterProbability = 0.5;
    this->clusteringParams.iterationUntilMissingImprovementCausesInterruption = 1000;
    this->clusteringParams.enqueueFrequency = 100;
    this->clusteringParams.logFrequency = 100;
    this->clusteringParams.explorationMutationChance = 0.05;
    this->clusteringParams.refinementMutationChance = 0.20;
    this->clusteringParams.crossoverIterationCount = 250;
    this->clusteringParams.minPopulationSize = 100;
    this->clusteringParams.maxPopulationSize = 500;
    this->clusteringParams.minIterations = 10000;
    this->clusteringParams.maxIterations = 100000;
    this->clusteringParams.minFitness = 1.4;
    this->clusteringParams.maxFitness = 1.7;
    this->clusteringParams.phaseSwitchFitnessValue = 1.4;
    this->clusteringParams.phaseSwitchIterationValue = 5000;
    this->clusteringParams.threadCount = 4;
    this->clusteringParams.fitnessFunction = 0;
}

ConfigurationManager::~ConfigurationManager()
{
}


ClusteringParams ConfigurationManager::getClusteringParams()
{
    return this->clusteringParams;
}

bool ConfigurationManager::getReevaluateUniquePopulation()
{
    return this->clusteringParams.reevaluateUniquePopulation;
}

bool ConfigurationManager::getUniquePopulationSelection()
{
    return this->clusteringParams.uniquePopulationSelection;
}

double ConfigurationManager::getMaxMinDensityClusterProbability()
{
    return this->clusteringParams.maxMinDensityClusterProbability;
}

uint64_t ConfigurationManager::getIterationUntilMissingImprovementCausesInterruption()
{
    return this->clusteringParams.iterationUntilMissingImprovementCausesInterruption;
}

uint64_t ConfigurationManager::getEnqueueFrequency()
{
    return this->clusteringParams.enqueueFrequency;
}

uint64_t ConfigurationManager::getLogFrequency()
{
    return this->clusteringParams.logFrequency;
}

double ConfigurationManager::getExplorationMutationChance()
{
    return this->clusteringParams.explorationMutationChance;
}

double ConfigurationManager::getRefinementMutationChance()
{
    return this->clusteringParams.refinementMutationChance;
}

uint64_t ConfigurationManager::getCrossoverIterationCount()
{
    return this->clusteringParams.crossoverIterationCount;
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

uint32_t ConfigurationManager::getFitnessFunction()
{
    return this->clusteringParams.fitnessFunction;
}

void ConfigurationManager::setClusteringParams(const ClusteringParams& clusteringParams)
{
    this->clusteringParams = clusteringParams;
}

void ConfigurationManager::setReevaluateUniquePopulation(bool reevaluateUniquePopulation)
{
    this->clusteringParams.reevaluateUniquePopulation = reevaluateUniquePopulation;
}

void ConfigurationManager::setUniquePopulationSelection(bool uniquePopulationSelection)
{
    this->clusteringParams.uniquePopulationSelection = uniquePopulationSelection;
}

void ConfigurationManager::setMaxMinDensityClusterProbability(double maxMinDensityClusterProbability)
{
    this->clusteringParams.maxMinDensityClusterProbability = maxMinDensityClusterProbability;
}

void ConfigurationManager::setIterationUntilMissingImprovementCausesInterruption(uint64_t iterationUntilMissingImprovementCausesInterruption)
{
    this->clusteringParams.iterationUntilMissingImprovementCausesInterruption = iterationUntilMissingImprovementCausesInterruption;
}

void ConfigurationManager::setEnqueueFrequency(uint64_t enqueueFrequency)
{
    this->clusteringParams.enqueueFrequency = enqueueFrequency;
}

void ConfigurationManager::setLogFrequency(uint64_t logFrequency)
{
    this->clusteringParams.logFrequency = logFrequency;
}

void ConfigurationManager::setExplorationMutationChance(double explorationMutationChance)
{
    this->clusteringParams.explorationMutationChance = explorationMutationChance;
}

void ConfigurationManager::setRefinementMutationChance(double refinementMutationChance)
{
    this->clusteringParams.refinementMutationChance = refinementMutationChance;
}

void ConfigurationManager::setCrossoverIterationCount(uint64_t crossoverIterationCount)
{
    this->clusteringParams.crossoverIterationCount = crossoverIterationCount;
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

void ConfigurationManager::setFitnessFunction(uint32_t fitnessFunction)
{
    this->clusteringParams.fitnessFunction = fitnessFunction;
}

void ConfigurationManager::loadClusteringParams(const std::string& fullPathName)
{
    ConfigurationReaderWriter configReader(fullPathName);
    std::unordered_map<std::string, std::string> parameterMap = configReader.readConfiguration();

    // go through the map and assign our parameters
    std::unordered_map<std::string, std::string>::iterator iter;

    iter = parameterMap.find("reevaluateUniquePopulation");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.reevaluateUniquePopulation = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find reevaluateUniquePopulation value in configuration file.");
        throw std::runtime_error("Error! Could not find reevaluateUniquePopulation value in configuration file.");
    }

    iter = parameterMap.find("uniquePopulationSelection");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.uniquePopulationSelection = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find uniquePopulationSelection value in configuration file.");
        throw std::runtime_error("Error! Could not find uniquePopulationSelection value in configuration file.");
    }

    iter = parameterMap.find("maxMinDensityClusterProbability");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.maxMinDensityClusterProbability = std::stod(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find maxMinDensityClusterProbability value in configuration file.");
        throw std::runtime_error("Error! Could not find maxMinDensityClusterProbability value in configuration file.");
    }

    iter = parameterMap.find("iterationUntilMissingImprovementCausesInterruption");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.iterationUntilMissingImprovementCausesInterruption = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find iterationUntilMissingImprovementCausesInterruption value in configuration file.");
        throw std::runtime_error("Error! Could not find iterationUntilMissingImprovementCausesInterruption value in configuration file.");
    }

    iter = parameterMap.find("enqueueFrequency");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.enqueueFrequency = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find enqueueFrequency value in configuration file.");
        throw std::runtime_error("Error! Could not find enqueueFrequency value in configuration file.");
    }

    iter = parameterMap.find("logFrequency");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.logFrequency = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find logFrequency value in configuration file.");
        throw std::runtime_error("Error! Could not find logFrequency value in configuration file.");
    }

    iter = parameterMap.find("explorationMutationChance");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.explorationMutationChance = std::stod(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find explorationMutationChance value in configuration file.");
        throw std::runtime_error("Error! Could not find explorationMutationChance value in configuration file.");
    }

    iter = parameterMap.find("refinementMutationChance");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.refinementMutationChance = std::stod(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find refinementMutationChance value in configuration file.");
        throw std::runtime_error("Error! Could not find refinementMutationChance value in configuration file.");
    }

    iter = parameterMap.find("crossoverIterationCount");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.crossoverIterationCount = std::stoull(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find crossoverIterationCount value in configuration file.");
        throw std::runtime_error("Error! Could not find crossoverIterationCount value in configuration file.");
    }

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

    iter = parameterMap.find("fitnessFunction");
    if (iter != parameterMap.end())
    {
        this->clusteringParams.fitnessFunction = std::stoul(iter->second);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find fitnessFunction value in configuration file.");
        throw std::runtime_error("Error! Could not find fitnessFunction value in configuration file.");
    }
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Loaded Clustering Params succesfully from the following file. File: ", fullPathName);
}

void ConfigurationManager::saveClusteringParams(const std::string& fullPathName)
{
    std::unordered_map<std::string, std::string> parameterMap;
    parameterMap["uniquePopulationSelection"] = std::to_string(this->clusteringParams.uniquePopulationSelection ? 1 : 0);
    parameterMap["reevaluateUniquePopulation"] = std::to_string(this->clusteringParams.reevaluateUniquePopulation ? 1 : 0);
    parameterMap["maxMinDensityClusterProbability"] = std::to_string(this->clusteringParams.maxMinDensityClusterProbability);
    parameterMap["iterationUntilMissingImprovementCausesInterruption"] = std::to_string(this->clusteringParams.iterationUntilMissingImprovementCausesInterruption);
    parameterMap["enqueueFrequency"] = std::to_string(this->clusteringParams.enqueueFrequency);
    parameterMap["logFrequency"] = std::to_string(this->clusteringParams.logFrequency);
    parameterMap["explorationMutationChance"] = std::to_string(this->clusteringParams.explorationMutationChance);
    parameterMap["refinementMutationChance"] = std::to_string(this->clusteringParams.refinementMutationChance);
    parameterMap["crossoverIterationCount"] = std::to_string(this->clusteringParams.crossoverIterationCount);
    parameterMap["minPopulationSize"] = std::to_string(this->clusteringParams.minPopulationSize);
    parameterMap["maxPopulationSize"] = std::to_string(this->clusteringParams.maxPopulationSize);
    parameterMap["minIterations"] = std::to_string(this->clusteringParams.minIterations);
    parameterMap["maxIterations"] = std::to_string(this->clusteringParams.maxIterations);
    parameterMap["minFitness"] = std::to_string(this->clusteringParams.minFitness);
    parameterMap["maxFitness"] = std::to_string(this->clusteringParams.maxFitness);
    parameterMap["phaseSwitchFitnessValue"] = std::to_string(this->clusteringParams.phaseSwitchFitnessValue);
    parameterMap["phaseSwitchIterationValue"] = std::to_string(this->clusteringParams.phaseSwitchIterationValue);
    parameterMap["threadCount"] = std::to_string(this->clusteringParams.threadCount);
    parameterMap["fitnessFunction"] = std::to_string(this->clusteringParams.fitnessFunction);

    ConfigurationReaderWriter configWriter(fullPathName);
    configWriter.writeConfiguration(parameterMap);
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Saved Clustering Params succesfully to the following file. File: ", fullPathName);
}

}
}
