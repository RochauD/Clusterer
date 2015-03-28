/**
 * @file CrossoverEngine.hpp
 * @brief crossover interface
 */
#ifndef CLUSTERER_BACKEND_CROSSOVER_ENGINE_HPP
#define CLUSTERER_BACKEND_CROSSOVER_ENGINE_HPP

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "ClusterEncoding.hpp"

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

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
