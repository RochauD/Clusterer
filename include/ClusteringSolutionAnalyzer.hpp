/**
* @file ClusteringSolutionAnalyzer.hpp
* @brief fitness function interface
*/
#ifndef CLUSTERER_BACKEND_CLUSTERING_SOLUTION_ANALYZER_HPP
#define CLUSTERER_BACKEND_CLUSTERING_SOLUTION_ANALYZER_HPP

// standard headers

// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "AbstractGraph.hpp"

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
* @class ClusteringSolutionAnalyzer
* @brief interface for objects which can assess the quality of a particular
* clustering scheme
*/
class ClusteringSolutionAnalyzer
{
    public:
        /**
        * @brief report a score for a clustering solution
        * @param clusteringSolution a clustering solution
        * @param graph The graph.
        * @return a score corresponding to the clustering solution
        * @pre The graph needs to have atleast on edge. In other words the graph is not allowed
        * totally disconnected.
        */
        virtual double analyze(const ClusterEncoding& clusteringSolution, const AbstractGraph& graph) = 0;

        /**
        * @brief standard destructor
        */
        virtual ~ClusteringSolutionAnalyzer() = 0;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
