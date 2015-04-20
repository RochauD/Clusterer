/**
 * @file UniformCrossoverEngine.hpp
 * @brief Interface of uniform crossover
 */
#ifndef CLUSTERER_BACKEND_UNIFROM_CROSSOVER_ENGINE_HPP
#define CLUSTERER_BACKEND_UNIFROM_CROSSOVER_ENGINE_HPP

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
 * @class UniformCrossoverEngine
 * @brief Interface for the uniform crossover method
 */
class UniformCrossoverEngine : public virtual CrossoverEngine
{
    public:
        /**
         * @brief Performs a Crossover on 2 encodings and creates a new one.
         *  It is necessary to call normalize on the parents if using integer encoding 
         * @param parent1 The first NORMALIZED parent contributing to the crossover
         * @param parent2 The second NORMALIZED parent contributing to the crossover
         * @param child The encoding object that will hold the child
         */
        void crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2,
                       ClusterEncoding& child);
        
        /**
         * @brief Performs a Crossover on 2 encodings and creates two ones.
         *  It is necessary to call normalize on the parents if using integer encoding 
         * @param parent1 The first NORMALIZED parent contributing to the crossover
         * @param parent2 The second NORMALIZED parent contributing to the crossover
         * @param child1 The encoding object that will hold the first child
         * @param child2 The encoding object that will hold the second child
         */
        void crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2,
                       ClusterEncoding& child1, ClusterEncoding& child2);
        
        /**
         * @brief Uniform Crossover constructor
         * @param gen An mt19937 random generator
         */
        UniformCrossoverEngine(std::mt19937* gen = NULL);

        /**
         * @brief standard destructor
         */
        ~UniformCrossoverEngine();

    private:
        /**
         * @brief Returns true or false with probability 50%
         * @return A random boolean
         */
        bool getTrueOrFalse();
        /**
         * @brief A [0, 1] integer distribution
         */
        std::bernoulli_distribution dist;
        /**
         * @brief Standard configuration of a random number generator
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
