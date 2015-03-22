/**
  * @file MutationEngine.hpp
  * @brief crossover implementation
  */
#ifndef _BACKEND_GENETIC_EXPLORATIONCROSSOVERENGINE_HPP
#define _BACKEND_GENETIC_EXPLORATIONCROSSOVERENGINE_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoder.hpp"

namespace backend {
namespace genetic {

class ExplorationCrossover: public CrossoverEngine {
 public:
     /**
      * @brief mutate a clustering solution
      * @param cluster the clustering solution to mutate
      * @param probability the probability with which the mutation will occur
      * @return the new clustering solution if a mutation occurred, or the old
      * one otherwise
      */
     virtual ClusterEncoder::Encoding
         crossover(const ClusterEncoder::Encoding& cluster,
              const ClusterEncoder::Encoding& cluster);

     /**
      * @brief standard destructor
      */
     virtual ~ExplorationCrossover();
};

}  // namespace genetic
}  // namespace backend

#endif  // include guard

