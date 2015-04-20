/**
* @file ExplorationJoin.cpp
* @brief mutation interface implementation
*/

//external headers
#include <chrono>
//local headers
#include "../include/ExplorationJoin.hpp"

namespace clusterer
{
namespace backend
{

ExplorationJoin::ExplorationJoin(std::mt19937* rand_gen) : MutationEngine()
{

    gen = rand_gen;
}

ExplorationJoin::~ExplorationJoin()
{
}

void ExplorationJoin::mutate(ClusterEncoding& clusterSol)
{
    int n = clusterSol.size();

    std::uniform_int_distribution<uint64_t> vDist(0,n-1);

    // at least 2 clusters needed
    if (clusterSol.getClusterCount() <= 1) { return; }

    //cluster id's to be joined
    ClusterId clusterId1 = clusterSol.getClusterOfVertex(vDist((*gen)));
    ClusterId clusterId2 = clusterSol.getClusterOfVertex(vDist((*gen)));
    // make sure the cluster id's are different
    while (clusterId1 == clusterId2) { clusterId2 = clusterSol.getClusterOfVertex(vDist((*gen))); }

    for (int i = 0; i < n; i++)
    {
        if (clusterSol.getClusterOfVertex(i) == clusterId2)
        { clusterSol.addToCluster(i,clusterId1); }
    }
}


} //namespace backend
} //namespace clusterer