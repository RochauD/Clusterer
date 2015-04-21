/**
* @file ExplorationMutation.cpp
* @brief mutation interface implementation
*/

//external headers
#include <chrono>
//local headers
#include "../include/ExplorationMutation.hpp"

namespace clusterer
{
namespace backend
{

ExplorationMutation::ExplorationMutation(std::mt19937* rand_gen) : MutationEngine()
{
    gen = rand_gen;
}

ExplorationMutation::~ExplorationMutation()
{
}

void ExplorationMutation::mutate(ClusterEncoding& clusterSol)
{

    ClusterEncoding::Encoding cluster = clusterSol.getEncoding();

    //find the biggest cluster id number
    std::vector<ClusterId>::iterator it;
    ClusterId maxId = *(cluster.begin());
    for (it = cluster.begin(); it != cluster.end(); ++it)
    {
        if (maxId < (*it)) { maxId = *it; }
    }

    std::uniform_int_distribution<uint64_t> intDist(0,maxId);

    // new cluster Id
    ClusterId new_clusterId = intDist((*gen));

    std::uniform_int_distribution<uint64_t> vDist(0,cluster.size()-1);

    VertexId lucky_vertex = vDist((*gen));

    clusterSol.addToCluster(lucky_vertex,new_clusterId);
    clusterSol.normalize();
}

} //namespace backend
} //namespace clusterer