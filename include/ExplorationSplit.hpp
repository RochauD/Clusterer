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

class ExplorationSplit: public MutationEngine
{
    public:
        /**
        * @brief empty constructor
        */
        ExplorationSplit(std::mt19937* rand_gen);

        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         */
        // splits a cluster into 2 clusters
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        ~ExplorationSplit();

    private:
        std::mt19937* gen;
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
