/**
* @file ExplorationMutation.cpp
* @brief mutation interface implementation
*/

//external headers
#include <chrono>
#include <iostream>
//local headers
#include "../include/ExplorationMutation.hpp"

namespace clusterer
{
namespace backend
{

ExplorationMutation::ExplorationMutation(){
    // setting the seed for the pseudo-random number generator
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen.seed(seed);
}

ExplorationMutation::~ExplorationMutation(){
	//dtor
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
    ClusterId new_clusterId = intDist(gen);

    std::uniform_int_distribution<uint64_t> vDist(0,cluster.size()-1);

    VertexId lucky_vertex = vDist(gen);

    clusterSol.addToCluster(lucky_vertex,new_clusterId);
}

void ExplorationMutation::split(ClusterEncoding& clusterSol){
    int n = clusterSol.size();

    std::uniform_int_distribution<uint64_t> vDist(0,n-1);

    //cluster Id to be changed
    ClusterId clusterIdToChange = clusterSol.getClusterOfVertex(vDist(gen));
    
    // pick 2 new cluster ids
    ClusterId clusterId1 = vDist(gen);
    ClusterId clusterId2 = vDist(gen);

    for(int i = 0; i < n; i++){
        if(clusterSol.getClusterOfVertex(i) == clusterIdToChange){
            if(bd(gen)) clusterSol.addToCluster(i,clusterId1); 
            else clusterSol.addToCluster(i,clusterId2);
        }
    }

}


} //namespace backend
} //namespace clusterer