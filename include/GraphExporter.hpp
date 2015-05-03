/**
 * @file GraphExporter.hpp
 * @brief Export graph to files.
 */
#ifndef CLUSTERER_BACKEND_GRAPH_EXPORTER_HPP
#define CLUSTERER_BACKEND_GRAPH_EXPORTER_HPP

// standard headers
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>

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

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{
class GraphExporter
{
    public:
        /**
         * @brief default constructor
         */
        GraphExporter() = default;

        /**
        * @brief standard destructor
        */
        ~GraphExporter() = delete;

        /**
        * @brief default constructor
        * @return bool value. true is writing was successful
        * @param g pointer to an Abstract Graph
        * @param fullPathName the fullpathname
        */
        bool WriteGraphToFile(AbstractGraph* g, std::string fullPathName);

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
