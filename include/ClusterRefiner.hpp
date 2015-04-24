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
        * @brief constructor to initialize the local gen pointer and
        * the necessary probability for the bernoulli distribution
        * @param pointer to an std::mt19937 object
        * @param probability, if not passed is set to 0.5
        */
        ClusterRefiner(std::mt19937 *rand_gen, double prob = 0.5);

        /**
        * @brief cluster refiner implementation
        * @param an encoding solution
        * @param graph reference
        */
        void refine(ClusterEncoding& clusterSol, const AbstractGraph& g);

        // the following 3 functions are useful for the testing units
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
        * @brief for debugging purposes if needed
        * @param an encoding solution
        */
        void printSol(const ClusterEncoding& clusterSol);

        std::mt19937 *gen;
        std::bernoulli_distribution bd;
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