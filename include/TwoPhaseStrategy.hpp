/**
 * @file TwoPhaseStrategy.hpp
 * @brief genetic strategy implementation
 */
#ifndef CLUSTERER_BACKEND_TWO_PHASE_STRATEGY_HPP
#define CLUSTERER_BACKEND_TWO_PHASE_STRATEGY_HPP

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "AbstractGraph.hpp"
#include "GeneticStrategy.hpp"

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

class TwoPhaseStrategy : public GeneticStrategy
{
    public:
        /**
         * @brief create a TwoPhaseStrategy based on a graph
         * @param g the graph on which the strategy is based
         */
        TwoPhaseStrategy(const AbstractGraph& g);
        /**
         * @brief obtain the next generation of the clustering solution
         * @return the order of the new generation
         */
        uint64_t runGeneticIteration();
        /**
         * @brief obtain the next generation of the exploration phase
         * @return the order of the new generation
         */
        uint64_t runExplorationIteration();
        /**
        * @brief obtain the next generation of the refinement phase
        * @return the order of the new generation
        */

        uint64_t runRefinementIteration();
        /**
         * @brief get the current clustering solution
         * @return the current clustering solution
         */
        ClusterEncoding::Encoding getClusteringSolution();

        ~TwoPhaseStrategy();

        /**
         * @brief get the maximum fitness value encountered until now
         * @return the max fitness value
         */
        double getMaxFitness();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
