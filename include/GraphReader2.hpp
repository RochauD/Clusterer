/**
 * @file GraphReader2.hpp
 * @brief class to read a graph from a file
 */
#ifndef CLUSTERER_BACKEND_GRAPH_READER2_HPP
#define CLUSTERER_BACKEND_GRAPH_READER2_HPP

// standard headers
#include <stdint.h>
#include <vector>
#include <stdio.h>
// external headers

// internal headers
#include "AbstractGraph.hpp"
#include "Graph.hpp"

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
 * @class GraphReader2
 * @brief interface to read a file into an abstract graph
 * There might be many possible input formats to the social clustering program,
 * but in every case we need to read the data in a graph.
 * This class provides the interface for doing so:
 * When a new input format is needed, just implement this interface for that
 * particular input format.
 */
class GraphReader2
{
    public:
        /**
         * @brief initalize a reader to read data into a graph
         * @param g the graph in which the data will be read
         */
        GraphReader2(Graph*);
        /**
         * @brief read file data into graph
         * @return 0 on success
         *         1 on failure
         */
        int readFile(std::string);
        /**
        * @brief get the filename
        * @return string
        */
        std::string getFileName();
        /**
        * @brief get the pointer to a Vertex object corresponding to a VertexId
        * @return Vertex pointer
        */
        Vertex* getVertex(VertexId);
        /**
        * @brief get the map from VertexId to a Vertex type object
        * @return the map
        */
        std::map<VertexId,Vertex> getVertexIdMap();
        /**
         * @brief standard destructor
         */
        virtual ~GraphReader2();
    protected:
        /**
        * @var _graph
        * @brief pointer to the Graph object which contains the information read
        * from file in a graph representation
        */
        Graph* _graph;
        /**
        * @var filename
        * @brief string containing the filename passed for reading
        */
        std::string filename;
        /**
        * @var vertex_map
        * @brief a map between VertexId, representative of a Vertex object,
        * and the Vertex object itself 
        */
        std::map<VertexId,Vertex> VertexId_map;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
