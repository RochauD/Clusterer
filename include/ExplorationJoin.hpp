/**
 * @file ExplorationJoin.hpp
 * @brief mutation interface implementation
 */
#ifndef CLUSTERER_BACKEND_EXPLORATION_JOIN_HPP
#define CLUSTERER_BACKEND_EXPLORATION_JOIN_HPP

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

class ExplorationJoin: public MutationEngine
{
    public:
        /**
        * @brief empty constructor
        */
        ExplorationJoin(std::mt19937* rand_gen);

        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         */
        // joins 2 clusters into 1 cluster
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        virtual ~ExplorationJoin();

    private:
        std::mt19937* gen;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
