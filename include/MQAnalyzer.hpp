/**
 * @file MQAnalyzer.hpp
 * @brief fitness function interface implementation
 */
#ifndef CLUSTERER_BACKEND_MQ_ANALYZER_HPP
#define CLUSTERER_BACKEND_MQ_ANALYZER_HPP

// standard headers

// external headers

// internal headers
#include "ClusteringSolutionAnalyzer.hpp"

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

class MQAnalyzer : public ClusteringSolutionAnalyzer
{
    public:
        /**
         * @brief report a score for a clustering solution
         * @param clusteringSolution a clustering solution
         * @param graph The graph.
         * @return the modularization quality of the solution
         * @pre The graph needs to have atleast on edge. In other words the graph is not allowed
         * totally disconnected.
         */
        double analyze(const ClusterEncoding& clusteringSolution, const AbstractGraph& graph);

        ~MQAnalyzer();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
