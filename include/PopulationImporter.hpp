/**
* @file PopulationImporter.hpp
* @brief Imports a population from a file.
*/
#ifndef CLUSTERER_BACKEND_POPULATION_IMPORTER_HPP
#define CLUSTERER_BACKEND_POPULATION_IMPORTER_HPP

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
class PopulationImporter
{
    public:
        /**
        * @brief default constructor
        */
        PopulationImporter() = default;

        /**
        * @brief standard destructor
        */
        ~PopulationImporter() = default;

        /**
        * @brief Loads a population from the given file
        * @return bool value. true if loading was successful
        * @param fullPathName the full filename
        * @param the underlying graph
        * @param population pointer to a population
        */
        bool LoadPopulationFromFile(std::string fullPathName, AbstractGraph* graph, std::vector<std::pair<IntegerVectorEncoding, double>>* population);

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
