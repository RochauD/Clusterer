#include "../include/IntegerVectorEncoding.hpp"

namespace clusterer
{
namespace backend
{

IntegerEncodingInitializer::IntegerEncodingInitializer(
        common::types::graph& g, unsigned maxClusters = 0) : graph(g)
{
    if (maxClusters == 0 || maxClusters >= graph.getNoVertices())
    { maxClusters = graph.getNoVertices() - 1; }

    std::random_device rd;
    rng.seed(rd());
    uni_dist = new std::uniform_int_distribution<unsigned>(0, maxClusters);
}

IntegerVectorEncoding IntegerEncodingInitializer::getRandomSolution()
{
    IntegerVectorEncoding result(graph);
    for (vert = 0; vert < graph.getNoVertices(); vert++)
    { result.addToCluster(i, *uni_dist(rng)); }
    return result;
}

std::vector<IntegerVectorEncoding> IntegerEncodingInitializer::getInitialPopulation(int count)
{
    std::vector<IntegerVectorEncoding> result;
    for (i = 0; i < count; i++) 
    { result.push_back(getRandomSolution()); }
    return result;
}

}  // namespace backend
}  // namespace clusterer

#endif  // _BACKEND_GENETIC_IntegerEncodingInitializer_HPP

