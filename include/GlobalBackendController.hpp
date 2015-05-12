/**
* @file GlobalBackendController.hpp
* @brief File in which the GlobalBackendController is defined.
*/
#ifndef CLUSTERER_BACKEND_GLOBAL_BACKEND_CONTROLLER_HPP
#define CLUSTERER_BACKEND_GLOBAL_BACKEND_CONTROLLER_HPP

// standard headers
#include <string>
#include <mutex>
#include <atomic>
// external headers

// internal headers
#include "ClusteringService.hpp"

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
* @class GlobalBackendController
* @brief A singleton class which uses the ClusteringService class to implement a global backend controller.
* @details This class is a Singleton class which uses the class ClusteringService to implement a
* global multithreaded file backend controller.
*/
class GlobalBackendController
{
    public:
        /**
        * @brief Returns a ClusteringService instance to access the backend.
        * @details This function returns the singleton instance of the ClusteringService.
        * @return ClusteringService* A pointer to a ClusteringService.
        */
        static ClusteringService* instance();

    private:
        GlobalBackendController() {}
        static std::atomic<ClusteringService*> backendController;
        static std::mutex mutex;
};

}
}

/**
* @namespace clc
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clc = clusterer::common;

#endif
