/**
* @file CombinedMutation.cpp
* @brief mutation interface implementation
*/

//external headers
#include <chrono>
//local headers
#include "../include/CombinedMutation.hpp"

namespace clusterer
{
namespace backend
{

CombinedMutation::CombinedMutation(std::mt19937* rand_gen):
MutationEngine(){
    gen = rand_gen;

    join = ExplorationJoin(gen);
    mut = ExplorationMutation(gen);
    split = ExplorationSplit(gen);
    // setting the seed for the pseudo-random number generator
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen->seed(seed);


}

CombinedMutation::~CombinedMutation(){
}

void CombinedMutation::mutate(ClusterEncoding& clusterSol){
    std::uniform_int_distribution<uint64_t> vDist(0,2);
    uint64_t i = vDist(*gen);
    switch(i){
        case 0:
           mut.mutate(clusterSol);
           break;
        case 1:
           join.mutate(clusterSol);
           break;
        case 2:
           split.mutate(clusterSol);
           break;
        default:
           mut.mutate(clusterSol);
           break;
    }

}


} //namespace backend
} //namespace clusterer