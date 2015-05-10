/**
* @file CoverageAnalyzer.hpp
* @brief The file contains the class definiton of the class CoverageAnalyzer.
*/
#ifndef CLUSTERER_BACKEND_COVERAGE_ANALYZER_HPP
#define CLUSTERER_BACKEND_COVERAGE_ANALYZER_HPP

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

/**
* @class CoverageAnalyzer
* @brief The CoverageAnalyzer is a class that computes the coverage of a solution.
*/
class CoverageAnalyzer : public ClusteringSolutionAnalyzer
{
    public:
        /**
        * @brief Returns the coverage value for a clustering solution
        * @param clusteringSolution A clustering solution.
        * @param graph The graph.
        * @return The coverage value, which is a value in the interval [0.0, 1.0]
        * @pre The graph needs to have atleast on edge. In other words the graph is not allowed
        * totally disconnected.
        */
        double analyze(const ClusterEncoding* clusteringSolution, const AbstractGraph* graph);

        /**
        * @brief Standard Destructor.
        */
        ~CoverageAnalyzer();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
