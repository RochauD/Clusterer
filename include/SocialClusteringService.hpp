/**
  * @file SocialClusteringService.hpp
  * @brief Facade for backend items
  */
#ifndef _FRONTEND_SOCIALCLUSTERINGSERVICE_HPP
#define _FRONTEND_SOCIALCLUSTERINGSERVICE_HPP

//Standard libraries
#include <cstdint>
#include <string>
#include <functional>

//Own libraries
#include "QueryHandler.hpp"
#include "CrossoverEngine.hpp"
#include "MutationEngine.hpp"
#include "FitnessAnalyzer.hpp"
#include "IntegerVectorEncoder.hpp"
#include "GeneticStrategy.hpp"
#include "PersonDb.hpp"
#include "GraphReader.hpp"


namespace backend {

/**
 * @class PersonDb
 * @brief interface for databases which allow person insertion
 */
class SocialClusteringService {
 public:
     /**
      * @brief insert person in database
      * @param person to be inserted in the database
      * @return 0 on success and -1 on failure.
      */
     static SocialClusteringService& getService() {
         static SocialClusteringService service;
         return service;
     }

     /**
      * @brief process clustering input data
      * @param filePath the path to the input file
      * @return status EXIT_SUCESS or EXIT_FAILURE
      */
     int processSocialData(const std::string filePath);

 private:
     SocialClusteringService();
     SocialClusteringService(const SocialClusteringService&);

     IntegerVectorEncoder _clusterEncoder;
     CrossoverEngine _crossoverEngine;
     MutationEngine _mutationEngine;
     FitnessAnalyzer _fitnessAnalyzer;
     GeneticStrategy _geneticStrategy;
     GraphReader _graphReader;

     PersonDb _personDb;
};

}  // namespace backend

#endif  // _FRONTEND_SOCIALCLUSTERINGSERVICE_HPP

