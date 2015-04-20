/**
 * @file UniformCrossoverEngine.cpp
 * @brief Interface of uniform crossover
 */

// internal headers
#include "../include/UniformCrossoverEngine.hpp"
#include "../include/IntegerVectorEncoding.hpp"

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
    UniformCrossoverEngine::UniformCrossoverEngine(std::mt19937* gen)
    {
        rng = gen;
    }

    bool UniformCrossoverEngine::getTrueOrFalse()
    {
        return dist((*rng));
    }

    void UniformCrossoverEngine::crossover(const ClusterEncoding& parent1, 
                                           const ClusterEncoding& parent2,
                                           ClusterEncoding& child)
    {
        unsigned i;
        unsigned n = parent1.size();
        for (i = 0; i < n; i++)
        {
            // Put vertex i in the cluster it is in one of the parents
            // With probability 50% for picking each parent
            if (getTrueOrFalse() == true)
            {
                child.addToCluster(i, parent1.getClusterOfVertex(i));
            } 
            else
            {
                child.addToCluster(i, parent2.getClusterOfVertex(i));
            }
        }
        child.normalize();
    }

    void UniformCrossoverEngine::crossover(const ClusterEncoding& parent1, 
                                           const ClusterEncoding& parent2,
                                           ClusterEncoding& child1,
                                           ClusterEncoding& child2)
    {
        unsigned i;
        unsigned n = parent1.size();
        for (i = 0; i < n; i++)
        {
            // Put vertex i in the cluster it is in one of the parents
            // With probability 50% for picking each parent
            if (getTrueOrFalse() == true)
            {
                child1.addToCluster(i, parent1.getClusterOfVertex(i));
                child2.addToCluster(i, parent2.getClusterOfVertex(i));
            } 
            else
            {
                child1.addToCluster(i, parent2.getClusterOfVertex(i));
                child2.addToCluster(i, parent1.getClusterOfVertex(i));
            }
        }
        child1.normalize();
        child2.normalize();
    }

    UniformCrossoverEngine::~UniformCrossoverEngine() {}

}
}
