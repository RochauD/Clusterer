/**
 * @file PopulationExporter.hpp
 * @brief Export population to files.
 */
#ifndef CLUSTERER_BACKEND_POPULATION_EXPORTER
#define CLUSTERER_BACKEND_POPULATION_EXPORTER

// standard headers
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <string>
// external headers

// internal headers
#include "Graph.hpp"
#include "AbstractGraph.hpp"
#include "Vertex.hpp"
/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{
// just for reference 
// typedef std::vector<ClusterId> Encoding;
// typedef uint64_t ClusterId;
/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{
class GraphExporter{
public:
    /**
     * @brief default constructor
     */
    PopulationExporter () = default;
    /**
    * @brief default constructor
    * @return bool value. true is writing was successful
    * @param AbstractGraph* pointer to an Abstract Graph
    */
    bool WritePopulationToFile (Population*, std::string);
    /**
     * @brief standard destructor
     */
    ~PopulationExporter () = default;
    
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