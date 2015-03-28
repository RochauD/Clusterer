/**
 * @file GeneticStrategy.hpp
 * @brief genetic strategy interface
 */
#ifndef CLUSTERER_BACKEND_GENETIC_STRATEGY_HPP
#define CLUSTERER_BACKEND_GENETIC_STRATEGY_HPP

// standard headers
#include <stdint.h>
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
 * @class GeneticStrategy
 * @brief interface for objects which implement genetic algorithms.
 * GeneticStrategy is a facade around its multiple subcomponents
 */
class GeneticStrategy
{
    public:
        /**
         * @brief create a GeneticStrategy based on a graph
         * @param g the graph on which the strategy is based
         */
        GeneticStrategy(const AbstractGraph& g);
        /**
         * @brief obtain the next generation of the clustering solution
         * @return the order of the new generation
         */
        virtual uint64_t runGeneticIteration() = 0;

        /**
         * @brief get the current clustering solution
         * @return the current clustering solution
         */
        virtual ClusterEncoding::Encoding getClusteringSolution() = 0;

        /**
         * @brief standard destructor
         */
        virtual ~GeneticStrategy();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
