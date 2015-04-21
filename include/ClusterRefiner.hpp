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
#include "IntegerVectorEncoding.hpp"
#include "MutationEngine.hpp"
#include "AbstractGraph.hpp"
#include "Graph.hpp"


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

class ClusterRefiner{

    public:
        /**
        * @brief empty constructor
        */
        ClusterRefiner(std::mt19937 *rand_gen, double prob = 0.5);

        /**
        * @brief cluster refiner implementation
        * @param a cluster solution
        * @param graph reference
        */
        void refine(ClusterEncoding& clusterSol, const AbstractGraph& g);
        
        /**
        * @brief empty destructor
        */        
        ~ClusterRefiner();
    private:

        void computeClustersDensity(ClusterEncoding& clusterSol,
            const AbstractGraph& g);
        double getClusterDensity(ClusterId cid,ClusterEncoding& clusterSol,
            const AbstractGraph& g);

        std::mt19937 *gen;
        std::bernoulli_distribution bd;
        std::vector<double> clusters_density;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif