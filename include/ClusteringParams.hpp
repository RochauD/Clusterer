/**
* @file ClusteringParams.hpp
* @brief File in which the ClusteringParams structure is defined.
*/
#ifndef CLUSTERING_PARAMS_HPP
#define CLUSTERING_PARAMS_HPP

// standard headers
#include <cstdint>
// external headers

// internal headers


/**
* @namespace ClustererBackend
* @brief The namespace ClustererBackend is the namespace for the complete backend
* of the project.
*/
namespace ClustererBackend
{

/**
* @struct ClusteringParams
* @brief Clustering parameters for the social clustering algorithm.
* @details The struct ClusteringParams specifies the algorithm parameters for
* the social clustering algorithm.
*/
struct ClusteringParams
{
    /**
    * @var minIterations
    * @brief Minimum algorithm iteration count.
    * @details The member variable minIterations specifies the minimum number
    * of iterations, which need to be performed before the algorithm
    * terminates.
    */
    uint64_t minIterations;

    /**
    * @var maxIterations
    * @brief Maximum algorithm iteration count.
    * @details The member variable maxIterations specifies the maximum number
    * of iterations the algorithm is allowed to perform, before it needs to
    * stop.
    */
    uint64_t maxIterations;

    /**
    * @var minFitness
    * @brief Minimum fitness value.
    * @details The member variable minFitness defines the minimum fitness
    * value a cluster solution must obtain before the algorithm may terminate.
    */
    double minFitness;

    /**
    * @var maxFitness
    * @brief Maximum fitness value.
    * @details The member variable maxFitness defines the maximum fitness
    * value a cluster solution may have before the algorithm should terminate.
    */
    double maxFitness;

    /**
    * @var phaseSwitchFitnessValue
    * @brief Fitness value threshold for phase switch.
    * @details The member variable phaseSwitchFitnessValue defines the
    * fitness value threshold which should trigger the phase switch in the
    * algorithm.
    */
    double phaseSwitchFitnessValue;

    /**
    * @var phaseSwitchIterationValue
    * @brief Iteration value threshold for phase switch.
    * @details The member variable phaseSwitchFitnessValue defines the
    * iteration value which should trigger the phase switch in the algorithm.
    */
    uint64_t phaseSwitchIterationValue;

    /**
    * @var predictedClusterCount
    * @brief Predicted number of clusters in the solution.
    * @details The member variable predictedClusterCount defines the number
    * of clusters we predict to have in our clustering solution.
    */
    uint64_t predictedClusterCount;

    /**
    * @var threadCount
    * @brief Number of threads used in the algorithm computation.
    * @details The member variable threadCount specifies the number of
    * threads used in the computation of the clustering solution.
    */
    uint32_t threadCount;

};
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace ClustererBackend.
*/
namespace clb = ClustererBackend;

#endif
