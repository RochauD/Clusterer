/**
 * @file MutationEngine.hpp
 * @brief mutation interface implementation
 */
#ifndef CLUSTERER_BACKEND_REFINEMENT_MUTATION_ENGINE_HPP
#define CLUSTERER_BACKEND_REFINEMENT_MUTATION_ENGINE_HPP

// standard headers
#include <stdint.h>
// external headers

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

class RefinementMutationEngine: public MutationEngine
{
    public:
        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         * @param probability the probability with which the mutation will occur
         * @return the new clustering solution if a mutation occurred, or the old
         * one otherwise
         */
        virtual ClusterEncoding::Encoding mutate(const ClusterEncoding::Encoding& cluster,
                double probability);

        /**
         * @brief Standart destructor
         */
        virtual ~RefinementMutationEngine();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
