/**
  * @file MQAnalyzer.hpp
  * @brief fitness function interface implementation
  */
#ifndef _BACKEND_GENETIC_MQANALYZER_HPP
#define _BACKEND_GENETIC_MQANALYZER_HPP

//Standard libraries
#include <stdint.h>

//Own libraries
#include "ClusterEncoder.hpp"

namespace backend
{
namespace genetic
{


class MQAnalyzer : public FitnessAnalyzer
{
public:
    typedef Score double;
    /**
     * @brief report a score for a clustering solution
     * @param clusteringSolution a clustering solution
     * @return a score corresponding to the clustering solution
     */
    virtual Score
    analyze(const ClusterEncoder::Encoding& clusteringSolution);

    virtual ~MQAnalyzer();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_MQANALYZER_HPP
