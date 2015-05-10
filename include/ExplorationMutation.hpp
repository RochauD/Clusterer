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

/**
* @class ExplorationMutation
* @brief The ExplorationMutation class is a class implements a simple mutation.
*/
class ExplorationMutation: public MutationEngine
{
    public:
        /**
        * @brief Constructor
        * @param rand_gen The random engine.
        */
        ExplorationMutation(std::mt19937* rand_gen);

        /**
         * @brief Mutate a clustering solution by choosing a new ClusterId based on the maximum ClusterId in the cluster.
         * @param clusterSol The clustering solution to mutate.
         */
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        ~ExplorationMutation();

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
