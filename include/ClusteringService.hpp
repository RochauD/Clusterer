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
#include "ConfigurationManager.hpp"
#include "ConcurrentLockingQueue.hpp"
#include "Graph.hpp"
#include "IntegerEncodingInitializer.hpp"
#include "TwoPhaseStrategy.hpp"
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
 * @class ClusteringService
 * @brief A facade that provides access to the backend.
 */
class ClusteringService
{
    public:
        ClusteringService();
        ~ClusteringService();

        // config related functions
        bool loadConfiguration(std::string fullPathName);
        bool saveConfiguration(std::string fullPathName);
        ClusteringParams getConfigurationParameters();

        // graph related functions
        bool loadGraphTypeVertexPairWeight(std::string fullPathName);

        // algorithm related functions

        bool runAlgorithm(bool restart = false);

        void stopAlgorithm();
        void resumeAlgorithm();

        // output related
        clc::ConcurrentLockingQueue<std::pair<IntegerVectorEncoding, double>>* getOutQueue();

    protected:
    private:
        TwoPhaseStrategy<IntegerVectorEncoding, IntegerEncodingInitializer> algorithmService;
        clc::ConcurrentLockingQueue<std::pair<IntegerVectorEncoding, double>> outQueue;
        std::vector<std::pair<IntegerVectorEncoding, double>> population;
        ConfigurationManager configurationManager;
        Graph graph;


        /**
        * @var serviceMutex
        * @brief Mutex.
        * @details Mutex will be used for mutual exclusion of thread ownership.
        */
        std::mutex serviceMutex;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
