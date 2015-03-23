/**
  * @file MutationEngine.hpp
  * @brief mutation interface
  */
#ifndef _BACKEND_GENETIC_MUTATIONENGINE_HPP
#define _BACKEND_GENETIC_MUTATIONENGINE_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoder.hpp"

namespace backend
{
namespace genetic
{

/**
 * @class MutationEngine
 * @brief interface for objects which allow mutating a particular configuration
 * with a given probability
 */
class MutationEngine
{
public:
    /**
     * @brief mutate a clustering solution
     * @param cluster the clustering solution to mutate
     * @param probability the probability with which the mutation will occur
     * @return the new clustering solution if a mutation occurred, or the old
     * one otherwise
     */
    virtual ClusterEncoder::Encoding
    mutate(const ClusterEncoder::Encoding& cluster,
           double probability) = 0;

    /**
     * @brief standard destructor
     */
    virtual ~MutationEngine();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_MUTATIONENGINE_HPP

