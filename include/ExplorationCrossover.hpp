/**
  * @file MutationEngine.hpp
  * @brief crossover implementation
  */
#ifndef _BACKEND_GENETIC_EXPLORATIONCROSSOVERENGINE_HPP
#define _BACKEND_GENETIC_EXPLORATIONCROSSOVERENGINE_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoding.hpp"

namespace backend
{
namespace genetic
{

class ExplorationCrossover: public CrossoverEngine
{
public:
    /**
     * @brief mutate a clustering solution
     * @param cluster the clustering solution to mutate
     * @param probability the probability with which the mutation will occur
     * @return the new clustering solution if a mutation occurred, or the old
     * one otherwise
     */
    virtual ClusterEncoding::Encoding
    crossover(const ClusterEncoding::Encoding& cluster,
              const ClusterEncoding::Encoding& cluster);

    /**
     * @brief standard destructor
     */
    virtual ~ExplorationCrossover();
};

}  // namespace genetic
}  // namespace backend

#endif  // include guard

