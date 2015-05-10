/**
* @file ClusterRefiner.hpp
* @brief cluster refining interface implementation
*/
#ifndef CLUSTERER_BACKEND_CLUSTER_REFINER_HPP
#define CLUSTERER_BACKEND_CLUSTER_REFINER_HPP

// standard headers
#include <stdint.h>
#include <random>
#include <vector>

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
* @class ClusterRefiner
* @brief A cluster refiner.
*/
class ClusterRefiner
{

    public:
        /**
        * @brief Constructor of the class.
        * @param rand_gen The random number generator.
        * @param prob The mutation probability.
        */
        ClusterRefiner(std::mt19937* rand_gen, double prob = 0.5);

        /**
        * @brief cluster refiner implementation
        * @param clusterSol An encoding of a solution.
        * @param g A reference to graph.
        */
        void refine(ClusterEncoding& clusterSol, const AbstractGraph& g);

        // the following 2 functions are useful for the testing units
        /**
        * @brief get the original's solution chosen cluster's density
        * @return the value
        */
        double getOriginalClusterRefineDensity();

        /**
        * @brief get option1 cluster's density
        * @return the value
        */
        double getAfterClusterRefineDensity();

        /**
        * @brief empty destructor
        */
        ~ClusterRefiner();
    private:
        /**
        * @brief compute the clusters density and store it in clusters_density
        * @param an encoding solution
        * @param graph reference
        */
        void computeClustersDensity(ClusterEncoding& clusterSol,
                                    const AbstractGraph& g);
        /**
        * @brief compute a specific cluster's density
        * @param a cluster id
        * @param an encoding solution
        * @param graph reference
        */
        double getClusterDensity(ClusterId cid,ClusterEncoding& clusterSol,
                                 const AbstractGraph& g);

        /**
        * @var gen
        * @brief A pointer to random number engine.
        */
        std::mt19937* gen;

        /**
        * @var bd
        * @brief A bernoulli distribution.
        */
        std::bernoulli_distribution bd;

        /**
        * @var clusters_density
        * @brief The cluster density vector.
        */
        std::vector<double> clusters_density;

        /**
        * @brief for testing purposes
        */
        double original_density;
        double after_density;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif