/**
* @file ExplorationMutation.cpp
* @brief mutation interface implementation
*/

//standard headers
#include <cstdlib> /*srand*/
#include <ctime> /*time*/

//local headers
#include "../include/ExplorationMutation.hpp"

namespace clusterer
{
namespace backend
{

ExplorationMutation::ExplorationMutation(){
	//empty ctor
}

ExplorationMutation::~ExplorationMutation(){
	//dtor
}

void ExplorationMutation::mutate(ClusterEncoding& clusterSol,
               double probability, ClusterEncoding& result){
    result = clusterSol;
    ClusterEncoding::Encoding cluster = clusterSol.getEncoding(); 
    
    // if the probability is not between 0 and 1 perform no mutation, and return
    // the cluster as it is
    if(probability < 0 || probability > 1) return;

    srand(time(NULL));
    // chance random number between 0 and 1
    double chance = rand()/double(RAND_MAX);
    // no mutation if probability is not enough
    if(probability < chance) return;

    //find the biggest clustering number
    std::vector<ClusterId>::iterator it;
    ClusterId maxId = *(cluster.begin());
    for(it = cluster.begin(); it != cluster.end(); ++it){
        if(maxId < (*it)) maxId = *it;
    }

    ClusterId new_clusterId = rand()%maxId+1;
    while(new_clusterId == maxId) new_clusterId = rand()%maxId+1;

    int i=0;
    VertexId lucky_vertex = rand()%cluster.size();

    for(it = cluster.begin(); it != cluster.end(); ++it){
    	if(i == lucky_vertex) result.addToCluster(lucky_vertex,new_clusterId);
    	i++;
    }
}

void ExplorationMutation::mutate2(ClusterEncoding& clusterSol,
               double probability, ClusterEncoding& result){

    result = clusterSol;
    ClusterEncoding::Encoding cluster = clusterSol.getEncoding();

    
    // if the probability is not between 0 and 1 perform no mutation, and return
    // the cluster as it is
    if(probability < 0 || probability > 1) return;

    srand(time(NULL));
    // chance random number between 0 and 1
    double chance = rand()/double(RAND_MAX);
    // no mutation if probability is not enough
    if(probability < chance) return;

    int i=0;
    VertexId lucky_vertex = rand()%cluster.size();
    ClusterId new_clusterId = rand()%cluster.size();
    // make sure the new clusterId is different than the current one
    while(new_clusterId == cluster.at(lucky_vertex)) new_clusterId = rand()%cluster.size();

    std::vector<ClusterId>::iterator it;
    for(it = cluster.begin(); it != cluster.end(); ++it){
    	if(i == lucky_vertex) result.addToCluster(lucky_vertex, new_clusterId);
    	i++;
    }
}

} //namespace backend
} //namespace clusterer