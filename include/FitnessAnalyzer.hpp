/**
 * @file FitnessAnalyzer.hpp
 * @brief fitness function interface
 */
#ifndef CLUSTERER_BACKEND_FITNESS_ANALYZER_HPP
#define CLUSTERER_BACKEND_FITNESS_ANALYZER_HPP

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
 * @class FitnessAnalyzer
 * @brief interface for objects which can assess the value of a particular
 * clustering scheme
 */
class FitnessAnalyzer
{
    public:
        typedef double Score;
        /**
         * @brief report a score for a clustering solution
         * @param clusteringSolution a clustering solution
         * @return a score corresponding to the clustering solution
         */
        virtual Score analyze(const ClusterEncoding::Encoding& clusteringSolution, const AbstractGraph& graph) = 0;

        /**
         * @brief standard destructor
         */
        virtual ~FitnessAnalyzer();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
