/**
* @file ExplorationMutation.cpp
* @brief mutation interface implementation
*/

//standard headers
#include <cstdlib> /*srand*/
#include <ctime> /*time*/

//local headers
#include "../include/ExplorationMutation"

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

ClusterEncoding::Encoding ExplorationMutation::mutate(const ClusterEncoding::Encoding& cluster,
               double probability){
    ClusterEncoding::Encoding mutated_version;
    
    // if the probability is not between 0 and 1 perform no mutation, and return
    // the cluster as it is
    if(probability < 0 || probability > 1) return cluster;

    srand(time(NULL));
    // chance random number between 0 and 1
    double chance = rand()/double(RAND_MAX);
    // no mutation if probability is not enough
    if(probability < chance) return cluster;

    //find the biggest clustering number
    std::vector<ClusterId>::iterator it;
    ClusterId maxId = *(cluster.begin());
    for(it = cluster.begin(); it != cluster.end(); ++it){
        if(maxId < (*it)) maxId = *it;
    }

    ClusterId new_clusterId = rand()%maxId+1;
    while(new_clusterId == maxId) new_clusterId = rand()%maxId+1;

    int i=0;
    int lucky_vertex = rand()%cluster.size();

    for(it = cluster.begin(); it != cluster.end(); ++it){
    	if(i == lucky_vertex) mutated_version.push_back(new_clusterId);
    	else mutated_version.push_back(*it);
    	i++;
    }

    return mutated_version;
}

ClusterEncoding::Encoding ExplorationMutation::mutate2(const ClusterEncoding::Encoding& cluster,
               double probability){
    ClusterEncoding::Encoding mutated_version;
    
    // if the probability is not between 0 and 1 perform no mutation, and return
    // the cluster as it is
    if(probability < 0 || probability > 1) return cluster;

    srand(time(NULL));
    // chance random number between 0 and 1
    double chance = rand()/double(RAND_MAX);
    // no mutation if probability is not enough
    if(probability < chance) return cluster;

    int i=0;
    int lucky_vertex = rand()%cluster.size();
    ClusterId new_clusterId = rand()%cluster.size();
    // make sure the new clusterId is different than the current one
    while(new_clusterId == cluster.at(lucky_vertex)) new_clusterId = rand()%cluster.size();

    std::vector<ClusterId>::iterator it;
    for(it = cluster.begin(); it != cluster.end(); ++it){
    	if(i == lucky_vertex) mutated_version.push_back(new_clusterId);
    	else mutated_version.push_back(*it);
    	i++;
    }

    return mutated_version;
}

} //namespace backend
} //namespace clusterer