/**
 * @file PerformanceAnalyzer.hpp
 * @brief fitness function interface implementation
 */
#ifndef CLUSTERER_BACKEND_PERFORMANCE_ANALYZER_HPP
#define CLUSTERER_BACKEND_PERFORMANCE_ANALYZER_HPP

// standard headers

// external headers

// internal headers
#include "ClusteringSolutionAnalyzer.hpp"
#include "CoverageAnalyzer.hpp"

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

class PerformanceAnalyzer : public ClusteringSolutionAnalyzer
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
        double analyze(const ClusterEncoding* clusteringSolution, const AbstractGraph* graph);

        ~PerformanceAnalyzer();
    protected:
    private:
        CoverageAnalyzer coverageAnalyzer;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
