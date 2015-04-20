/**
 * @file CrossoverEngine.cpp
 * @brief crossover implementation
 */
#include "../include/CrossoverEngine.hpp"

namespace clusterer
{

namespace backend
{


// Dumb implementations makes sure methods are not purely virtual

void CrossoverEngine::crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2,
                                ClusterEncoding& child)
{
  for (int i = 0; i < parent1.size(); i++)
  {
      child.addToCluster(i, parent1.getClusterOfVertex(i));
  }
}
void CrossoverEngine::crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2, 
                                ClusterEncoding& child1, ClusterEncoding& child2)
{
    for (int i = 0; i < parent1.size(); i++)
    {
        child1.addToCluster(i, parent1.getClusterOfVertex(i));
        child2.addToCluster(i, parent2.getClusterOfVertex(i));
    }
}


}   //end namespace backend
}   //end namespace clusterer