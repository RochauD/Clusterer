/**
  * @file PerformanceAnalyzer.hpp
  * @brief fitness function interface implementation
  */
#ifndef _BACKEND_GENETIC_PERFORMANCEANALYZER_HPP
#define _BACKEND_GENETIC_PERFORMANCEANALYZER_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoder.hpp"

namespace backend
{
namespace genetic
{


class PerformanceAnalyzer : public FitnessAnalyzer
{
public:
    typedef Score double;
    /**
     * @brief report a score for a clustering solution
     * @param clusteringSolution a clustering solution
     * @return a score corresponding to the clustering solution
     */
    virtual Score analyze(const ClusterEncoder::Encoding& clusteringSolution);

    virtual ~PerformanceAnalyzer();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_PERFORMANCEANALYZER_HPP

