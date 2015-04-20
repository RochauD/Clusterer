/**
 * @file CombinedCrossoverEngine.cpp
 * @brief combined crossover implementation
 */
#include "../include/CombinedCrossoverEngine.hpp"

namespace clusterer
{

namespace backend
{

UniformCrossoverEngine::UniformCrossoverEngine(std::mt19937* gen)
{
    rng = gen;
    uniformCrossover = new UniformCrossoverEngine(rng);
    clusterwiseCrossover = new ClusterwiseCrossoverEngine(rng);
}

UniformCrossoverEngine::~UniformCrossoverEngine()
{
    delete uniformCrossover;
    delete clusterwiseCrossover;
}

void CrossoverEngine::crossover(const ClusterEncoding& parent1, const ClusterEncoding& parent2, 
                                ClusterEncoding& child1, ClusterEncoding& child2)
{
    bool uniform = dist((*rng));

    if (uniform)
    {
        uniformCrossover->crossover(parent1, parent2, child1, child2);
    }
    else
    {
        clusterwiseCrossover->crossover(parent1, parent2, child1, child2);
    }
}


}   //end namespace backend
}   //end namespace clusterer