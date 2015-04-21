/**
* @file PerformanceAnalyzer.hpp
* @brief PerformanceAnalyzer implementation.
*/

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "../include/PerformanceAnalyzer.hpp"

namespace clusterer
{
namespace backend
{

double PerformanceAnalyzer::analyze(const ClusterEncoding* clusteringSolution, const AbstractGraph* graph)
{
    auto clusterVerticesMap = clusteringSolution->getClusterVerticesCountMap();
    uint32_t verticesCount = graph->getNoVertices();
    uint32_t clusterCount = clusterVerticesMap.size();
    double coverageValue = this->coverageAnalyzer.analyze(clusteringSolution, graph);
    uint64_t sumOfClusterSizes = 0;
    double totalEdgeWeightSum = 0.0;

    for (auto& e : graph->getEdgesAndWeights())
    {
        totalEdgeWeightSum += e.second;
    }

    for (size_t i = 0; i < clusterCount; ++i)
    {
        auto currentClusterSize = clusterVerticesMap[i];
        sumOfClusterSizes += (currentClusterSize * (currentClusterSize - 1));
    }
    return 1 - ((2 * totalEdgeWeightSum *(1 - 2 * coverageValue) + sumOfClusterSizes) / (verticesCount*(verticesCount - 1)));
}

PerformanceAnalyzer::~PerformanceAnalyzer()
{

}

}
}
