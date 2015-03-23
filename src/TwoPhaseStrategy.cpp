/**
  * @file TwoPhaseStrategy.hpp
  * @brief genetic strategy implementation
  */


#include <stdint.h>

#include "../include/ClusterEncoder.hpp"
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

double TwoPhaseStrategy::getMaxFitness()
{
    return 0.0;
}

}  // namespace genetic
}  // namespace backend



