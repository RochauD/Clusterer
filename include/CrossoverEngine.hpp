/**
  * @file CrossoverEngine.hpp
  * @brief crossover interface
  */
#ifndef _BACKEND_GENETIC_CROSSOVERENGINE_HPP
#define _BACKEND_GENETIC_CROSSOVERENGINE_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoding.hpp"

namespace backend
{
namespace genetic
{


/**
 * @class CrossoverEngine
 * @brief interface for objects that allow encoding crossovers
 */
class CrossoverEngine
{
public:
    /**
     * @brief crossover 2 encodings to create a new one
     * @param parent1 the first parent contributing to the crossover
     * @param parent2 the second parent contributing to the crossover
     * @return the new clustering encoding
     */
    virtual ClusterEncoding::Encoding
    crossover(const ClusterEncoding::Encoding& parent1,
              const ClusterEncoding::Encoding& parent2) = 0;

    /**
     * @brief standard destructor
     */
    virtual ~CrossoverEngine();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_CROSSOVERENGINE_HPP

