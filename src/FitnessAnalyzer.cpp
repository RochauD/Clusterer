/**
* @file FitnessAnalyzer.hpp
* @brief FitnessAnalyzer implementation.
*/

// standard headers
#include <stdint.h>
// external headers

// internal headers
#include "../include/FitnessAnalyzer.hpp"

namespace clusterer
{
namespace backend
{

double FitnessAnalyzer::analyze(const ClusterEncoding* clusteringSolution, const AbstractGraph* graph)
{
    auto mqValue = this->mqAnalyzer.analyze(clusteringSolution, graph);
    auto performanceValue = this->performanceAnalyzer.analyze(clusteringSolution, graph);
    return (1 + mqValue) / 2 + performanceValue;
}

FitnessAnalyzer::~FitnessAnalyzer()
{

}

}
}
