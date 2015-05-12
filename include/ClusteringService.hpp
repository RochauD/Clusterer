/**
* @file ClusteringService.hpp
* @brief This file contains the class ClusteringService which is a Facade for backend items.
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
#include "PopulationMember.hpp"
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
        /**
        * @brief Standard Constructor.
        */
        ClusteringService();

        /**
        * @brief Standard Destructor.
        */
        ~ClusteringService();

        /**
        * @brief This method loads a configuration.
        * @param fullPathName The full path name to the configuration file.
        * @return True if loading was succesful and False if it failed.
        */
        bool loadConfiguration(std::string fullPathName);

        /**
        * @brief This method saves a configuration.
        * @param fullPathName The full path name to the configuration file.
        * @return True if saving was succesful and False if it failed.
        */
        bool saveConfiguration(std::string fullPathName);

        /**
        * @brief This method returns the current ClusteringParams.
        * @return The current ClusteringParams.
        */
        ClusteringParams getConfigurationParameters();

        /**
        * @brief this method returns a graph object
        * @return the graph
        */
        Graph getGraph();

        /**
        * @brief This method sets the current ClusteringParams.
        * @param clusteringParams The ClusteringParams.
        * @return void
        */
        void setConfigurationParameters(const ClusteringParams& clusteringParams);

        /**
        * @brief This method loads a graph of type vertex pair weight.
        * @param fullPathName The full path name to the graph file.
        * @return True if loading was succesful and False if it failed.
        */
        bool loadGraphTypeVertexPairWeight(std::string fullPathName);

        /**
        * @brief This method loads a graph type of movie lens from a file.
        * @param fullPathName The full path name to the graph file.
        * @return True if loading was succesful and False if it failed.
        */
        bool loadGraphTypeMovieLens(std::string fullPathName);

        /**
        * @brief This method saves a graph to a file.
        * @param fullPathName The full path name of the output graph file.
        * @return True if saving was succesful and False if it failed.
        */
        bool saveGraphToFile(std::string fullPathName);

        /**
        * @brief This method loads a population from a file.
        * @param fullPathName The full path name of the input population file.
        * @return True if loading was succesful and False if it failed.
        */
        bool loadPopulation(std::string fullPathName);

        /**
        * @brief This method saves a population to a file.
        * @param fullPathName The full path name of the output population file.
        * @return True if saving was succesful and False if it failed.
        */
        bool savePopulation(std::string fullPathName);

        /**
        * @brief This method runs the algorithm.
        * @param restart Boolean restart flag. If set to true we are restarting.
        * @return void
        */
        bool runAlgorithm(bool restart = false);

        /**
        * @brief This method stops the algorithm.
        * @return void
        */
        void stopAlgorithm();

        /**
        * @brief This method resumes the algorithm.
        * @return void
        */
        void resumeAlgorithm();

        /**
        * @brief This method returns the current output queue.
        * @return The current output queue.
        */
        clc::ConcurrentLockingQueue<std::pair<PopulationMember<IntegerVectorEncoding, double>, uint64_t>>* getOutQueue();

    protected:
    private:
        /**
        * @var algorithmService
        * @brief The underlying algorithm service.
        */
        TwoPhaseStrategy<IntegerVectorEncoding, IntegerEncodingInitializer> algorithmService;

        /**
        * @var outQueue
        * @brief The output concurrent queue that is used to send data to the connect frontend.
        */
        clc::ConcurrentLockingQueue<std::pair<PopulationMember<IntegerVectorEncoding, double>, uint64_t>> outQueue;

        /**
        * @var population
        * @brief The population of the algorithm.
        */
        std::vector<PopulationMember<IntegerVectorEncoding, double>> population;

        /**
        * @var configurationManager
        * @brief The ConfigurationManager object that stores the algorithm parameters.
        */
        ConfigurationManager configurationManager;

        /**
        * @var graph
        * @brief The graph.
        */
        Graph graph;

        /**
        * @var serviceMutex
        * @brief The Mutex.
        */
        std::mutex serviceMutex;


        std::mutex workerMutex;
        std::condition_variable workerCV;
        std::unique_ptr<std::thread> workerThread;
        bool workerFlag;
        int runningFlag;


        void executeAlgoService();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
