#include "../include/IntegerEncodingInitializer.hpp"

namespace clusterer
{
namespace backend
{

IntegerEncodingInitializer::IntegerEncodingInitializer(
        const Graph* g, unsigned maxClusters) : graph(g)
{
    if (maxClusters == 0 || maxClusters >= graph->getNoVertices())
    { maxClusters = graph->getNoVertices() - 1; }

    std::random_device rd;
    rng.seed(rd());
    uni_dist = new std::uniform_int_distribution<unsigned>(0, maxClusters);
}

IntegerVectorEncoding IntegerEncodingInitializer::getRandomSolution()
{
    IntegerVectorEncoding result(graph);
    for (int vert = 0; vert < graph->getNoVertices(); vert++)
    { result.addToCluster(vert, (*uni_dist)(rng)); }
    result.normalize();
    return result;
}

std::vector<IntegerVectorEncoding> IntegerEncodingInitializer::getInitialPopulation(int count)
{
    std::vector<IntegerVectorEncoding> result;
    for (int i = 0; i < count; i++) 
    { result.push_back(getRandomSolution()); }
    return result;
}

}  // namespace backend
}  // namespace clusterer

