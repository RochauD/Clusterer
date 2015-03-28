/**
 * @file SocialClusteringService.hpp
 * @brief Facade for backend items
 */
#ifndef CLUSTERER_BACKEND_SOCIAL_CLUSTERING_SERVICE_HPP
#define CLUSTERER_BACKEND_SOCIAL_CLUSTERING_SERVICE_HPP

// standard headers
#include <cstdint>
#include <string>
#include <functional>
// external headers

// internal headers
#include "CrossoverEngine.hpp"
#include "MutationEngine.hpp"
#include "FitnessAnalyzer.hpp"
#include "IntegerVectorEncoding.hpp"
#include "GeneticStrategy.hpp"
#include "PersonDb.hpp"
#include "GraphReader.hpp"

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{

/**
 * @class PersonDb
 * @brief interface for databases which allow person insertion
 */
class SocialClusteringService
{
    public:
        /**
         * @brief insert person in database
         * @param person to be inserted in the database
         * @return 0 on success and -1 on failure.
         */
        static SocialClusteringService& getService()
        {
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

        ClusterEncoding* _ClusterEncoding;
        CrossoverEngine* _crossoverEngine;
        MutationEngine* _mutationEngine;
        FitnessAnalyzer* _fitnessAnalyzer;
        GeneticStrategy* _geneticStrategy;
        GraphReader* _graphReader;

        PersonDb* _personDb;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
