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

double PerformanceAnalyzer::analyze(const ClusterEncoding& clusteringSolution, const AbstractGraph& graph)
{

    auto clusterVerticesMap = clusteringSolution.getClusterVerticesCountMap();
    double verticesCount = clusterVerticesMap.size();
    uint32_t clusterCount = clusteringSolution.getClusterCount();
    double coverageValue = this->coverageAnalyzer.analyze(clusteringSolution, graph);
    uint64_t sumOfClusterSizes = 0;
    double totalEdgeWeightSum = 0.0;

    for (auto& e : graph.getEdges())
    {
        totalEdgeWeightSum += e.weight;
    }

    for (size_t i = 0; i < clusterCount; ++i)
    {
        auto currentClusterSize = clusterVerticesMap[i];
        sumOfClusterSizes += (currentClusterSize * (currentClusterSize - 1));
    }
    return 1 - ((2 * totalEdgeWeightSum *(1 - 2 * coverageValue) + sumOfClusterSizes) / (clusterCount*(clusterCount - 1)));
}

PerformanceAnalyzer::~PerformanceAnalyzer()
{

}

}
}