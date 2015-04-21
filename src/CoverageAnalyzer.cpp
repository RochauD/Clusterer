/**
* @file CoverageAnalyzer.hpp
* @brief CoverageAnalyzer implementation.
*/

// standard headers

// external headers

// internal headers
#include "../include/CoverageAnalyzer.hpp"

namespace clusterer
{
namespace backend
{

double CoverageAnalyzer::analyze(const ClusterEncoding* clusteringSolution, const AbstractGraph* graph)
{
    double intraEdgeWeightSum = 0.0;
    double totalEdgeWeightSum = 0.0;

    for (auto& e : graph->getEdgesAndWeights())
    {
        if (clusteringSolution->getClusterOfVertex(e.first.first) == clusteringSolution->getClusterOfVertex(e.first.second))
        {
            intraEdgeWeightSum += e.second;
        }
        totalEdgeWeightSum += e.second;
    }

    return intraEdgeWeightSum / totalEdgeWeightSum;
}

CoverageAnalyzer::~CoverageAnalyzer()
{

}

}
}
