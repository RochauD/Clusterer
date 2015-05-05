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
// external headers

// internal headers
#include "AbstractGraph.hpp"
#include "Vertex.hpp"
#include "IntegerVectorEncoding.hpp"

namespace clusterer
{
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
        IntegerEncodingInitializer(const AbstractGraph* g, unsigned maxClusters = 0);

        /**
         * @brief Returns one randomly initialized clustering solution
         * @return A valid random solution to the clustering problem
         */
        IntegerVectorEncoding getRandomSolution();

        /**
         * @brief Generates an initial population for the genetic algorithm
         * @param The number of individuals in the initial population
         * @return A vector of randomly generated solutions
         */
        std::vector<IntegerVectorEncoding> getInitialPopulation(int chromosomeCount);

    protected:
        unsigned maxClusters;
        const AbstractGraph* graph;
        std::mt19937 rng;
        // TODO: Make this a smart pointer
        std::uniform_int_distribution<unsigned>* uni_dist;
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_IntegerEncodingInitializer_HPP
