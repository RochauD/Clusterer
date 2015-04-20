/**
* @file ExplorationSplit.cpp
* @brief mutation interface implementation
*/

//external headers

//local headers
#include "../include/ExplorationSplit.hpp"

namespace clusterer
{
namespace backend
{

ExplorationSplit::ExplorationSplit(std::mt19937* rand_gen) : MutationEngine()
{
    gen = rand_gen;
}

ExplorationSplit::~ExplorationSplit()
{
}

void ExplorationSplit::mutate(ClusterEncoding& clusterSol)
{
    int n = clusterSol.size();

    std::uniform_int_distribution<uint64_t> vDist(0,n-1);

    //cluster Id to be changed
    ClusterId clusterIdToChange = clusterSol.getClusterOfVertex(vDist(*this->gen));

    // pick 2 new cluster ids
    ClusterId clusterId1 = vDist((*gen));
    ClusterId clusterId2 = vDist((*gen));

    for (int i = 0; i < n; i++)
    {
        if (clusterSol.getClusterOfVertex(i) == clusterIdToChange)
        {
            if (bd(*gen)) { clusterSol.addToCluster(i,clusterId1); }
            else { clusterSol.addToCluster(i,clusterId2); }
        }
    }
    clusterSol.normalize();
}


} //namespace backend
} //namespace clusterer