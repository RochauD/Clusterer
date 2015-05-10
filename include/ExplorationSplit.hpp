/**
 * @file ExplorationSplit.hpp
 * @brief mutation interface implementation
 */
#ifndef CLUSTERER_BACKEND_EXPLORATION_SPLIT_HPP
#define CLUSTERER_BACKEND_EXPLORATION_SPLIT_HPP

// standard headers
#include <stdint.h>
#include <random>


// internal headers
#include "ClusterEncoding.hpp"
#include "MutationEngine.hpp"

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
* @class ExplorationSplit
* @brief The ExplorationSplit is a class that implements a splitting a mutation.
*/
class ExplorationSplit: public MutationEngine
{
    public:
        /**
        * @brief Constructor
        * @param rand_gen The random engine.
        */
        ExplorationSplit(std::mt19937* rand_gen);

        /**
         * @brief Mutate a clustering solution by splitting a cluster into two clusters.
         * @param clusterSol The clustering solution to mutate.
         */
        //
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        ~ExplorationSplit();

    private:
        /**
        * @var gen
        * @brief A pointer to random number engine.
        */
        std::mt19937* gen;

        /**
        * @var bd
        * @brief A bernoulli distribution.
        */
        std::bernoulli_distribution bd;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
