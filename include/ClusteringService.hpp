/**
 * @file ClusteringService.hpp
 * @brief Facade for backend items
 */
#ifndef CLUSTERER_BACKEND_CLUSTERING_SERVICE_HPP
#define CLUSTERER_BACKEND_CLUSTERING_SERVICE_HPP

// standard headers
#include <string>
// external headers

// internal headers


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
 * @class PersonDb
 * @brief interface for databases which allow person insertion
 */
class ClusteringService
{
    public:

    private:

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
