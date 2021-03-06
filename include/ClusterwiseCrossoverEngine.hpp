/**
 * @file ClusterwiseCrossoverEngine.hpp
 * @brief Interface of Clusterwise crossover.
 */
#ifndef CLUSTERER_BACKEND_CLUSTERWISE_CROSSOVER_ENGINE_HPP
#define CLUSTERER_BACKEND_CLUSTERWISE_CROSSOVER_ENGINE_HPP

// standard headers
#include <stdint.h>
#include <random>

// external headers

// internal headers
#include "CrossoverEngine.hpp"

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
* @class ClusterwiseCrossoverEngine
* @brief Interface for the Clusterwise crossover method.
*/
class ClusterwiseCrossoverEngine : public CrossoverEngine
{
    public:
        /**
         * @brief crossover 2 encodings to create two new ones
         * @param parent1 the first parent contributing to the crossover
         * @param parent2 the second parent contributing to the crossover
         * @param child1 The encoding object that will hold the first child
         * @param child2 The encoding object to hold the second child
         */
        void crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2,
                       ClusterEncoding& child1, ClusterEncoding& child2);

        /**
         * @brief Clusterwise Crossover constructor
         * @param gen An mt19937 random generator
         */
        ClusterwiseCrossoverEngine(std::mt19937* gen);

        /**
         * @brief standard destructor
         */
        ~ClusterwiseCrossoverEngine();

    private:
        /**
        * @var rng
        * @brief Pointer to a random number generator.
        */
        std::mt19937* rng;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
