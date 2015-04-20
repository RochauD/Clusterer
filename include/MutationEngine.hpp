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
        */
        virtual void mutate(ClusterEncoding& cluster) = 0;
        /**
         * @brief mutates a clustering solution
         * @param cluster the clustering solution to mutate 
        */
        virtual void split(ClusterEncoding& cluster) = 0;

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
