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

/**
* @class ExplorationJoin
* @brief The ExplorationJoin is a class that implements a joining mutation.
*/
class ExplorationJoin: public MutationEngine
{
    public:
        /**
        * @brief Constructor
        * @param rand_gen The random engine.
        */
        ExplorationJoin(std::mt19937* rand_gen);

        /**
        * @brief Mutates a clustering solution by joining two clusters into one cluster.
        * @param clusterSol The clustering solution to mutate.
        */
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        ~ExplorationJoin();

    private:
        /**
        * @var gen
        * @brief A pointer to random number engine.
        */
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
