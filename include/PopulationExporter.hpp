/**
 * @file PopulationExporter.hpp
 * @brief Export population to files.
 */
#ifndef CLUSTERER_BACKEND_POPULATION_EXPORTER_HPP
#define CLUSTERER_BACKEND_POPULATION_EXPORTER_HPP

// standard headers
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <string>
// external headers

// internal headers
#include "Vertex.hpp"
#include "IntegerVectorEncoding.hpp"

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

/*
* @class GraphExporter
*/
class PopulationExporter
{
    public:
        /**
         * @brief default constructor
         */
        PopulationExporter();

        /**
        * @brief standard destructor
        */
        ~PopulationExporter();

        /**
        * @brief default constructor
        * @return bool value. true is writing was successful
        * @param population pointer to the population
        * @param fullPathName the full filename
        */
        bool WritePopulationToFile(std::vector<std::pair<IntegerVectorEncoding, double>>* population, std::string fullPathName);

    protected:
    private:

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
