/**
* @file MutationEngine.hpp
* @brief crossover implementation
*/
#ifndef CLUSTERER_BACKEND_EXPLORATION_CROSSOVER_HPP
#define CLUSTERER_BACKEND_EXPLORATION_CROSSOVER_HPP

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "CrossoverEngine.hpp"

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

class ExplorationCrossover: public CrossoverEngine
{
    public:
        /**
         * @brief mutate a clustering solution
         * @param cluster the clustering solution to mutate
         * @param probability the probability with which the mutation will occur
         * @return the new clustering solution if a mutation occurred, or the old
         * one otherwise
         */
        virtual ClusterEncoding::Encoding
        crossover(const ClusterEncoding::Encoding& cluster,
                  const ClusterEncoding::Encoding& thisISWRONG);

        /**
         * @brief standard destructor
         */
        virtual ~ExplorationCrossover();
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
