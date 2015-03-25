/**
  * @file TwoPhaseStrategy.hpp
  * @brief genetic strategy implementation
  */
#ifndef _BACKEND_TWOPHASESTRATEGY_HPP
#define _BACKEND_TWOPHASESTRATEGY_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoding.hpp"
#include "AbstractGraph.hpp"
#include "GeneticStrategy.hpp"

namespace backend
{
namespace genetic
{

class TwoPhaseStrategy : public GeneticStrategy
{
    public:
        /**
         * @brief create a TwoPhaseStrategy based on a graph
         * @param g the graph on which the strategy is based
         */
        TwoPhaseStrategy(const common::types::AbstractGraph& g);
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

}  // namespace genetic
}  // namespace backend

#endif // include guard

