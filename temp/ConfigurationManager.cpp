#include "ConfigurationManager.hpp"

ConfigurationManager::ConfigurationManager()
{
	this->clusteringParams.minIterations = 10;
	this->clusteringParams.maxIterations = 1000;
	this->clusteringParams.minFitness = 100.0; //@todo add a good default value here
	this->clusteringParams.maxFitness = 1000.0;
	this->clusteringParams.phaseSwitchFitnessValue = 50.0;
	this->clusteringParams.phaseSwitchIterationValue = 700;
	this->clusteringParams.predictedClusterCount = 10;
	this->clusteringParams.threadCount = 2;
}

ConfigurationManager::~ConfigurationManager()
{
}


ClusteringParams ConfigurationManager::GetClusteringParams()
{
	return this->clusteringParams;
}

uint64_t ConfigurationManager::GetMinIterationsCount()
{
	return this->clusteringParams.minIterations;
}

uint64_t ConfigurationManager::GetMaxIterationsCount()
{
	return this->clusteringParams.maxIterations;
}

double ConfigurationManager::GetMinFitness()
{
	return this->clusteringParams.minFitness;
}

double ConfigurationManager::GetMaxFitness()
{
	return this->clusteringParams.maxFitness;
}

double ConfigurationManager::GetPhaseSwitchFitnessValue()
{
	return this->clusteringParams.phaseSwitchFitnessValue;
}

uint64_t ConfigurationManager::GetPhaseSwitchIterationValue()
{
	return this->clusteringParams.phaseSwitchIterationValue;
}

uint64_t ConfigurationManager::GetPredictedClusterCount()
{
	return this->clusteringParams.predictedClusterCount;
}

uint32_t ConfigurationManager::GetThreadCount()
{
	return this->clusteringParams.threadCount;
}


void ConfigurationManager::SetClusteringParams(const ClusteringParams& clusteringParams)
{
	this->clusteringParams = clusteringParams;
}

void ConfigurationManager::SetMinIterationsCount(uint64_t minIterations)
{
	this->clusteringParams.minIterations = minIterations;
}

void ConfigurationManager::SetMaxIterationsCount(uint64_t maxIterations)
{
	this->clusteringParams.maxIterations = maxIterations;
}

void ConfigurationManager::SetMinFitness(double minFitness)
{
	this->clusteringParams.minFitness = minFitness;
}

void ConfigurationManager::SetMaxFitness(double maxFitness)
{
	this->clusteringParams.maxFitness = maxFitness;
}

void ConfigurationManager::SetPhaseSwitchFitnessValue(double phaseSwitchFitnessValue)
{
	this->clusteringParams.phaseSwitchFitnessValue = phaseSwitchFitnessValue;
}

void ConfigurationManager::SetPhaseSwitchIterationValue(uint64_t phaseSwitchIterationValue)
{
	this->clusteringParams.phaseSwitchIterationValue = phaseSwitchIterationValue;
}

void ConfigurationManager::SetPredictedClusterCount(uint64_t predictedClusterCount)
{
	this->clusteringParams.predictedClusterCount = predictedClusterCount;
}

void ConfigurationManager::SetThreadCount(uint32_t threadCount)
{
	this->clusteringParams.threadCount = threadCount;
}


void ConfigurationManager::LoadClusteringParams(const std::string& fullPathName)
{
	ConfigurationReaderWriter configReader(fullPathName);
	std::unordered_map<std::string, std::string> parameterMap = configReader.readConfiguration();
	
	// go through the map and assign our parameters
	std::unordered_map<std::string, std::string>::iterator iter;
	iter = parameterMap.find("minIterations");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.minIterations = std::stoull(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find minIterations value in configuration file.");
	}

	iter = parameterMap.find("maxIterations");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.maxIterations = std::stoull(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find maxIterations value in configuration file.");
	}

	iter = parameterMap.find("minFitness");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.minFitness = std::stod(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find minFitness value in configuration file.");
	}

	iter = parameterMap.find("maxFitness");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.maxFitness = std::stod(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find maxFitness value in configuration file.");
	}

	iter = parameterMap.find("phaseSwitchFitnessValue");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.phaseSwitchFitnessValue = std::stod(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find phaseSwitchFitnessValue value in configuration file.");
	}

	iter = parameterMap.find("phaseSwitchIterationValue");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.phaseSwitchIterationValue = std::stoull(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find phaseSwitchIterationValue value in configuration file.");
	}

	iter = parameterMap.find("predictedClusterCount");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.predictedClusterCount = std::stoull(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find predictedClusterCount value in configuration file.");
	}

	iter = parameterMap.find("threadCount");
	if (iter != parameterMap.end())
	{
		this->clusteringParams.threadCount = std::stoul(iter->second);
	}
	else
	{
		throw std::runtime_error("Error! Could not find threadCount value in configuration file.");
	}

}

void ConfigurationManager::SaveClusteringParams(const std::string& fullPathName)
{
	std::unordered_map<std::string, std::string> parameterMap;
	parameterMap["minIterations"] = std::to_string(this->clusteringParams.minIterations);
	parameterMap["maxIterations"] = std::to_string(this->clusteringParams.maxIterations);
	parameterMap["minFitness"] = std::to_string(this->clusteringParams.minFitness);
	parameterMap["maxFitness"] = std::to_string(this->clusteringParams.maxFitness);
	parameterMap["phaseSwitchFitnessValue"] = std::to_string(this->clusteringParams.phaseSwitchFitnessValue);
	parameterMap["phaseSwitchIterationValue"] = std::to_string(this->clusteringParams.phaseSwitchIterationValue);
	parameterMap["predictedClusterCount"] = std::to_string(this->clusteringParams.predictedClusterCount);
	parameterMap["threadCount"] = std::to_string(this->clusteringParams.threadCount);

	ConfigurationReaderWriter configWriter(fullPathName);
	configWriter.writeConfiguration(parameterMap);
}
