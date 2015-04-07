#include "../include/IntegerVectorEncoding.hpp"

namespace backend
{
namespace genetic
{

IntegerEncodingInitializer::IntegerEncodingInitializer(
        common::types::graph& g, unsigned maxClusters = 0) : graph(g)
{
    if (maxClusters == 0 || maxClusters >= graph.getNoVertices())
        maxClusters = graph.getNoVertices() - 1;

    std::random_device rd;
    rng.seed(rd());
    uni_dist = new std::uniform_int_distribution<unsigned>(0, maxClusters);
}

IntegerVectorEncoding& IntegerEncodingInitializer::getRandomSolution()
{
    IntegerVectorEncoding result
}


}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_IntegerEncodingInitializer_HPP

