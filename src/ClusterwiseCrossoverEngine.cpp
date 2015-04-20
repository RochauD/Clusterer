/**
 * @file ClusterwiseCrossoverEngine.cpp
 * @brief Interface of Clusterwise crossover
 */

// own headers
#include "../include/ClusterwiseCrossoverEngine.hpp"
#include "../include/ClusterEncoding.hpp"

// standard headers
#include <algorithm>

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

ClusterwiseCrossoverEngine::ClusterwiseCrossoverEngine(std::mt19937* gen)
{
    if (gen == NULL)
    {
        gen = new std::mt19937();
    }
    rng = gen;
}

void ClusterwiseCrossoverEngine::crossover(const ClusterEncoding& parent1,
        const ClusterEncoding& parent2,
        ClusterEncoding& child1,
        ClusterEncoding& child2)
{
    // First make exact copies of the parents
    unsigned i;
    auto n = parent1.size();
    for (i = 0; i < n; i++)
    {
        child1.addToCluster(i, parent1.getClusterOfVertex(i));
        child2.addToCluster(i, parent2.getClusterOfVertex(i));
    }
    child1.normalize();
    child2.normalize();

    // Randomly get a cluster to exchange
    int possibleClusters = std::min(child1.getClusterCount(), child2.getClusterCount());
    std::uniform_int_distribution<unsigned> uni_dist(0, possibleClusters - 1);
    int exchangedCluster = uni_dist((*rng));

    for (i = 0; i < n; i++)
    {
        if (child1.getClusterOfVertex(i) == exchangedCluster ||
                child2.getClusterOfVertex(i) == exchangedCluster)
        {
            // Swap the clusterId for vertex i in the children
            int tmp = child1.getClusterOfVertex(i);
            child1.addToCluster(i, child2.getClusterOfVertex(i));
            child2.addToCluster(i, tmp);
        }

    }
    child1.normalize();
    child2.normalize();
}

ClusterwiseCrossoverEngine::~ClusterwiseCrossoverEngine() {}

}
}
