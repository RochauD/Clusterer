#include "../include/IntegerEncodingInitializer.hpp"

namespace clusterer
{
namespace backend
{

IntegerEncodingInitializer::IntegerEncodingInitializer(
    const AbstractGraph* g, unsigned maxClusters, uint32_t functionFlag)
{
    this->graph = g;
    this->functionFlag = functionFlag;
    this->maxClusters = maxClusters;
    if (this->maxClusters == 0 || this->maxClusters >= graph->getNoVertices())
    {
        this->maxClusters = graph->getNoVertices() - 1;
    }

    std::random_device rd;
    rng.seed(rd());
    uni_dist = new std::uniform_int_distribution<unsigned>(0, this->maxClusters);
}

IntegerVectorEncoding IntegerEncodingInitializer::getRandomSolution()
{
    IntegerVectorEncoding result(graph);
    ClusterEncoding::Encoding encoding;
    encoding.resize(graph->getNoVertices());

    switch (this->functionFlag)
    {
        case 0:
            {
                for (uint64_t vert = 0; vert < graph->getNoVertices(); vert++)
                {
                    result.addToCluster(vert, (*uni_dist)(rng));
                }
            }
            break;
        case 1:
            {
                uint64_t numberOfElementsPerCluster = this->graph->getNoVertices() / this->maxClusters;
                uint64_t leftOverElements = this->graph->getNoVertices() % this->maxClusters;
                uint64_t curNumberOfElementsCount;
                size_t lastIndex = 0;

                for (uint64_t j = 0; j < this->maxClusters; ++j)
                {
                    if (leftOverElements > 0)
                    {
                        curNumberOfElementsCount = numberOfElementsPerCluster + 1;
                        leftOverElements--;
                    }
                    else
                    {
                        curNumberOfElementsCount = numberOfElementsPerCluster;
                    }
                    for (size_t i = lastIndex; i < lastIndex+curNumberOfElementsCount; ++i)
                    {
                        encoding[i] = j;
                    }
                    lastIndex = lastIndex+curNumberOfElementsCount;
                }
                std::shuffle(encoding.begin(), encoding.end(), rng);
                result.setEncoding(encoding);
            }
            break;
        default:
            {
                for (uint64_t vert = 0; vert < graph->getNoVertices(); vert++)
                {
                    result.addToCluster(vert, (*uni_dist)(rng));
                }
            }
            break;
    }

    result.normalize();
    return result;
}

}
}
