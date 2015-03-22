/**
  * @file FitnessAnalyzer.hpp
  * @brief fitness function interface
  */
#ifndef _BACKEND_GENETIC_FITNESSANALYZER_HPP
#define _BACKEND_GENETIC_FITNESSANALYZER_HPP

#include <stdint.h>

#include "ClusterEncoder.hpp"
#include "Vertex.hpp"

namespace backend {
namespace genetic {


/**
 * @class FitnessAnalyzer
 * @brief interface for objects which can assess the value of a particular
 * clustering scheme
 */
class FitnessAnalyzer {
 public:
     typedef double Score;
     /**
      * @brief report a score for a clustering solution
      * @param clusteringSolution a clustering solution
      * @return a score corresponding to the clustering solution
      */
     virtual Score analyze(const typename ClusterEncoder::Encoding& clusteringSolution) = 0;

     /**
      * @brief standard destructor
      */
     virtual ~FitnessAnalyzer();
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_FITNESSANALYZER_HPP

