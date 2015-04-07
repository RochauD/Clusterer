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

double CoverageAnalyzer::analyze(const ClusterEncoding& clusteringSolution, const AbstractGraph& graph)
{
    double intraEdgeWeightSum = 0.0;
    double totalEdgeWeightSum = 0.0;

    for (auto& e : graph.getEdges())
    {
        if (clusteringSolution.getClusterOfVertex(e.startNode) == clusteringSolution.getClusterOfVertex(e.endNode))
        {
            intraEdgeWeightSum += e.weight;
        }
        totalEdgeWeightSum += e.weight;
    }
    return intraEdgeWeightSum / totalEdgeWeightSum;
}

CoverageAnalyzer::~CoverageAnalyzer()
{

}

}
}