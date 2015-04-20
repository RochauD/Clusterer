/**
* @file CombinedMutation.cpp
* @brief mutation interface implementation
*/

// external headers

// internal headers
#include "../include/CombinedMutation.hpp"

namespace clusterer
{
namespace backend
{

CombinedMutation::CombinedMutation(std::mt19937* rand_gen) : MutationEngine(), join(rand_gen), mut(rand_gen), split(rand_gen)
{
    this->gen = rand_gen;
}

CombinedMutation::~CombinedMutation()
{
}

void CombinedMutation::mutate(ClusterEncoding& clusterSol)
{
    std::uniform_int_distribution<uint64_t> vDist(0,2);
    uint64_t i = vDist(*gen);
    switch (i)
    {
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