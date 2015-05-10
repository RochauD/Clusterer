/**
  * @file IntegerEncodingInitializer.hpp
  * @brief Interface of initial population generator for IntegerVectorEncoding
  */
#ifndef BACKEND_GENETIC_INTEGER_ENCODING_INITALIZER_HPP
#define BACKEND_GENETIC_INTEGER_ENCODING_INITALIZER_HPP

// standard headers
#include <stdint.h>
#include <vector>
#include <random>
#include <algorithm>
// external headers

// internal headers
#include "AbstractGraph.hpp"
#include "Vertex.hpp"
#include "IntegerVectorEncoding.hpp"

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
 * @class IntegerEncodingInitializer
 * @interface for objects that allow a cluster to be encoded
 */
class IntegerEncodingInitializer
{
    public:
        /**
         * @brief Constructor for IntegerEncodingInitializer
         * @param The graph to be clustered
         * @param The maximum number of clusters in a solution (the number of vertices by default)
         */
        IntegerEncodingInitializer(const AbstractGraph* g, unsigned maxClusters = 0, uint32_t functionFlag = 0);

        /**
         * @brief Returns one randomly initialized clustering solution
         * @return A valid random solution to the clustering problem
         */
        IntegerVectorEncoding getRandomSolution();

    protected:
        unsigned maxClusters;
        const AbstractGraph* graph;
        std::mt19937 rng;
        uint32_t functionFlag;
        std::uniform_int_distribution<unsigned>* uni_dist;
};

}
}

#endif
