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

ExplorationMutation::ExplorationMutation(std::mt19937* rand_gen){

    if (rand_gen == NULL)
    {
        gen = new std::mt19937();
    } else gen = rand_gen;
    // setting the seed for the pseudo-random number generator
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen->seed(seed);
}

ExplorationMutation::~ExplorationMutation(){
	delete gen;
}

void ExplorationMutation::mutate(ClusterEncoding& clusterSol){
    
    ClusterEncoding::Encoding cluster = clusterSol.getEncoding();

    //find the biggest cluster id number
    std::vector<ClusterId>::iterator it;
    ClusterId maxId = *(cluster.begin());
    for(it = cluster.begin(); it != cluster.end(); ++it){
        if(maxId < (*it)) maxId = *it;
    }

    std::uniform_int_distribution<uint64_t> intDist(0,maxId);
    
    // new cluster Id
    ClusterId new_clusterId = intDist((*gen));

    std::uniform_int_distribution<uint64_t> vDist(0,cluster.size()-1);

    VertexId lucky_vertex = vDist((*gen));

    clusterSol.addToCluster(lucky_vertex,new_clusterId);
}

void ExplorationMutation::split(ClusterEncoding& clusterSol){
    int n = clusterSol.size();

    std::uniform_int_distribution<uint64_t> vDist(0,n-1);

    //cluster Id to be changed
    ClusterId clusterIdToChange = clusterSol.getClusterOfVertex(vDist(*gen));
    
    // pick 2 new cluster ids
    ClusterId clusterId1 = vDist((*gen));
    ClusterId clusterId2 = vDist((*gen));

    for(int i = 0; i < n; i++){
        if(clusterSol.getClusterOfVertex(i) == clusterIdToChange){
            if(bd(*gen)) clusterSol.addToCluster(i,clusterId1); 
            else clusterSol.addToCluster(i,clusterId2);
        }
    }
}

void ExplorationMutation::join(ClusterEncoding& clusterSol){
    int n = clusterSol.size();

    std::uniform_int_distribution<uint64_t> vDist(0,n-1);

    // at least 2 clusters needed
    if(clusterSol.getClusterCount() <= 1) return;

    //cluster id's to be joined 
    ClusterId clusterId1 = clusterSol.getClusterOfVertex(vDist((*gen)));
    ClusterId clusterId2 = clusterSol.getClusterOfVertex(vDist((*gen)));
    // make sure the cluster id's are different
    while(clusterId1 == clusterId2) clusterId2 = clusterSol.getClusterOfVertex(vDist((*gen)));

    for(int i = 0; i < n; i++){
        if(clusterSol.getClusterOfVertex(i) == clusterId2)
            clusterSol.addToCluster(i,clusterId1);
    }
}


} //namespace backend
} //namespace clusterer