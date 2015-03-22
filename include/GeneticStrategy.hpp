/**
  * @file GeneticStrategy.hpp
  * @brief genetic strategy interface
  */
#ifndef _BACKEND_GENETIC_GENETICSTRATEGY_HPP
#define _BACKEND_GENETIC_GENETICSTRATEGY_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoder.hpp"
#include "AbstractGraph.hpp"

namespace backend {
namespace genetic {

/**
 * @class GeneticStrategy
 * @brief interface for objects which implement genetic algorithms.
 * GeneticStrategy is a facade around its multiple subcomponents
 */
class GeneticStrategy {
 public:
     /** 
      * @brief create a GeneticStrategy based on a graph
      * @param g the graph on which the strategy is based
      */
     GeneticStrategy(const AbstractGraph& g);
     /**
      * @brief obtain the next generation of the clustering solution
      * @return the order of the new generation
      */
     virtual uint64_t runGeneticIteration() = 0;

     /**
      * @brief get the current clustering solution
      * @return the current clustering solution
      */
     virtual ClusterEncoder::Encoding getClusteringSolution() = 0;

     /**
      * @brief standard destructor
      */
     virtual ~GeneticStrategy();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_GENETICSTRATEGY_HPP

