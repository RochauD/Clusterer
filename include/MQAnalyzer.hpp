/**
 * @file MQAnalyzer.hpp
 * @brief fitness function interface implementation
 */
#ifndef CLUSTERER_BACKEND_MQ_ANALYZER_HPP
#define CLUSTERER_BACKEND_MQ_ANALYZER_HPP

// standard headers

// external headers

// internal headers
#include "FitnessAnalyzer.hpp"

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

class MQAnalyzer : public FitnessAnalyzer
{
    public:
        typedef double Score;
        /**
         * @brief report a score for a clustering solution
         * @param clusteringSolution a clustering solution
         * @return a score corresponding to the clustering solution
         */
        virtual Score analyze(const ClusterEncoding::Encoding& clusteringSolution, const AbstractGraph& graph);

        virtual ~MQAnalyzer();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
