/**
 * @file CombinedMutation.hpp
 * @brief mutation interface implementation
 */
#ifndef CLUSTERER_BACKEND_COMBINED_MUTATION_HPP
#define CLUSTERER_BACKEND_COMBINED_MUTATION_HPP

// standard headers
#include <stdint.h>
#include <random>


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

class CombinedMutation: public MutationEngine
{
    public:
        /**
        * @brief empty constructor
        */
        CombinedMutation(std::mt19937 *rand_gen);

        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         */
        // picks one of the 3 mutate functions to execute
        void mutate(ClusterEncoding& clusterSol);

        /**
         * @brief standard destructor
         */
        ~CombinedMutation();

    private:
        std::mt19937 *gen;
        ExplorationJoin join;
        ExplorationMutation mut;
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
