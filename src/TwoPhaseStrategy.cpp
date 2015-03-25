/**
  * @file TwoPhaseStrategy.hpp
  * @brief genetic strategy implementation
  */


#include <stdint.h>

#include "../include/ClusterEncoding.hpp"
#include "../include/AbstractGraph.hpp"
#include "../include/TwoPhaseStrategy.hpp"
#include "../include/GeneticStrategy.hpp"

namespace backend
{
namespace genetic
{


TwoPhaseStrategy::TwoPhaseStrategy(const common::types::AbstractGraph& g) : GeneticStrategy(g)
{

}

TwoPhaseStrategy::~TwoPhaseStrategy()
{

}

uint64_t TwoPhaseStrategy::runGeneticIteration()
{
    return 0;
}

uint64_t TwoPhaseStrategy::runExplorationIteration()
{
    return 0;
}

uint64_t TwoPhaseStrategy::runRefinementIteration()
{
    return 0;
}

ClusterEncoding::Encoding TwoPhaseStrategy::getClusteringSolution()
{
    ClusterEncoding::Encoding x;
    return x;
}

double TwoPhaseStrategy::getMaxFitness()
{
    return 0.0;
}

}  // namespace genetic
}  // namespace backend



