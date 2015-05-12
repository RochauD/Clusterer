/**
* @file CombinedMutation.hpp
* @brief A file which implements a combined mutation.
*/
#ifndef CLUSTERER_BACKEND_COMBINED_MUTATION_HPP
#define CLUSTERER_BACKEND_COMBINED_MUTATION_HPP

// standard headers
#include <stdint.h>
#include <random>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "MutationEngine.hpp"
#include "ExplorationJoin.hpp"
#include "ExplorationSplit.hpp"
#include "ExplorationMutation.hpp"

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
* @class CombinedMutation
* @brief CombinedMutator is a class that uses a several mutation functions to mutate a solution.
*/
class CombinedMutation: public MutationEngine
{
    public:
        /**
        * @brief Constructor which creates a combined mutation object.
        * @param rand_gen A pointer to a random number generator.
        */
        CombinedMutation(std::mt19937* rand_gen);

        /**
         * @brief Mutate a clustering solution by picking one of the 3 mutate functions to execute.
         * @param clusterSol The clustering solution to mutate.
         */
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        ~CombinedMutation();

    private:
        /**
        * @var gen
        * @brief A pointer to random number engine.
        */
        std::mt19937* gen;

        /**
        * @var join
        * @brief The ExplorationJoin function.
        */
        ExplorationJoin join;

        /**
        * @var mut
        * @brief The ExplorationMutation function.
        */
        ExplorationMutation mut;

        /**
        * @var split
        * @brief The ExplorationSplit function.
        */
        ExplorationSplit split;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
