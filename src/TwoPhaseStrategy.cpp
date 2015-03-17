/**
  * @file TwoPhaseStrategy.hpp
  * @brief genetic strategy implementation
  */

#include <stdint.h>
#include "../include/ClusterEncoder.hpp"
#include "../include/AbstractGraph.hpp"

namespace backend {
namespace genetic {


TwoPhaseStrategy::TwoPhaseStrategy(const AbstractGraph& g) : GeneticStrategy(g)
{

}
     
double TwoPhaseStrategy::getMaxFitness()
{
	return maxFitness;
}

}  // namespace genetic
}  // namespace backend



