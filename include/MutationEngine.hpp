/**
 * @file MutationEngine.hpp
 * @brief mutation interface
 */
#ifndef CLUSTERER_BACKEND_MUTATION_ENGINE_HPP
#define CLUSTERER_BACKEND_MUTATION_ENGINE_HPP

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "ClusterEncoding.hpp"

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
 * @class MutationEngine
 * @brief interface for objects which allow mutating a particular configuration
 * with a given probability
 */
class MutationEngine
{
    public:
        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         * @param probability the probability with which the mutation will occur
         * @return the new clustering solution if a mutation occurred, or the old
         * one otherwise
         */
        virtual void mutate(ClusterEncoding& cluster,double probability,
            ClusterEncoding& result) = 0;

        /**
         * @brief standard destructor
         */
        virtual ~MutationEngine();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
