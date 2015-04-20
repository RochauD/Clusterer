/**
 * @file CombinedCrossoverEngine.hpp
 * @brief random crossover interface
 */
#ifndef CLUSTERER_BACKEND_COMBINED_CROSSOVER_ENGINE_HPP
#define CLUSTERER_BACKEND_COMBINED_CROSSOVER_ENGINE_HPP

// standard headers
#include <stdint.h>
#include <random>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "UniformCrossoverEngine.hpp"
#include "ClusterwiseCrossoverEngine.hpp"


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
 * @class CombinedCrossoverEngine
 * @brief interface for objects that allow encoding crossovers
 */
class CombinedCrossoverEngine
{
    public:

        /**
         * @brief Combined Crossover constructor
         * @param gen An mt19937 random generator
         */
        CombinedCrossoverEngine(std::mt19937* gen);

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
         * @brief standard destructor
         */
        ~CombinedCrossoverEngine() {}
    private:
        /**
         * @brief Returns true or false with probability 50%
         * @return A random boolean
         */
        std::mt19937* rng;
        /**
         * @brief A [0, 1] integer distribution
         */
        std::bernoulli_distribution dist;

        UniformCrossoverEngine* uniformCrossover;
        ClusterwiseCrossoverEngine* clusterwiseCrossover;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
