/**
 * @file CombinedCrossoverEngine.cpp
 * @brief combined crossover implementation
 */
#include "../include/CombinedCrossoverEngine.hpp"

namespace clusterer
{
namespace backend
{

CombinedCrossoverEngine::CombinedCrossoverEngine(std::mt19937* gen) :
    uniformCrossover(gen), clusterwiseCrossover(gen)
{
    rng = gen;
}

CombinedCrossoverEngine::~CombinedCrossoverEngine()
{
}

void CombinedCrossoverEngine::crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2,
                                        ClusterEncoding& child1, ClusterEncoding& child2)
{
    bool uniform = dist((*rng));

    if (uniform)
    {
        uniformCrossover.crossover(parent1, parent2, child1, child2);
    }
    else
    {
        clusterwiseCrossover.crossover(parent1, parent2, child1, child2);
    }
}


}   //end namespace backend
}   //end namespace clusterer