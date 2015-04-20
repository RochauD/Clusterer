/**
 * @file ExplorationMutation.hpp
 * @brief mutation interface implementation
 */
#ifndef CLUSTERER_BACKEND_EXPLORATION_MUTATION_HPP
#define CLUSTERER_BACKEND_EXPLORATION_MUTATION_HPP

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

class ExplorationMutation: public MutationEngine
{
    public:
        /**
        * @brief empty constructor
        */
        ExplorationMutation();

        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         */
        // chooses a new ClusterId based on the maximum ClusterId in the cluster
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         */
        // splits a cluster into 2 clusters
        void split(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        virtual ~ExplorationMutation();

    private:
        std::mt19937 gen;
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
