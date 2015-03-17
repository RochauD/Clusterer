/**
  * @file SocialClusteringService.cpp
  * @brief implementation of Facade for backend items
  */

#include <cstdint>

#include <string>
#include <functional>

#include "common/daemon/QueryHandler.hpp"
#include "CrossoverEngine.hpp"
#include "MutationEngine.hpp"
#include "FitnessAnalyzer.hpp"
#include "IntegerVectorEncoder.hpp"
#include "GeneticStrategy.hpp"
#include "PersonDb.hpp"
#include "GraphReader.hpp"


namespace backend {


int SocialClusteringService::processSocialData(const std::string filePath)
{
  return 0;
}


SocialClusteringService::SocialClusteringService()
{

}

SocialClusteringService(const SocialClusteringService&)
{

}


}  // namespace backend

