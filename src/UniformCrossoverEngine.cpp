/**
 * @file UniformCrossoverEngine.cpp
 * @brief Interface of uniform crossover
 */

// internal headers
#include "../include/UniformCrossoverEngine.hpp"
#include "../include/IntegerVectorEncoding.hpp"

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{

    void UniformCrossoverEngine::crossover(const ClusterEncoding& parent1,
                                           const ClusterEncoding& parent2,
                                           ClusterEncoding& child)
    {
    }

    UniformCrossoverEngine::~UniformCrossoverEngine() {}

}
}
