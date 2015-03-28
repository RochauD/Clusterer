/**
 * @file GraphReader.hpp
 * @brief class to read a graph from a file
 */
#ifndef CLUSTERER_BACKEND_GRAPH_READER_HPP
#define CLUSTERER_BACKEND_GRAPH_READER_HPP

// standard headers
#include <stdint.h>
#include <stdio.h>
// external headers

// internal headers
#include "../include/AbstractGraph.hpp"

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
 * @class GraphReader
 * @brief interface to read a file into an abstract graph
 * There might be many possible input formats to the social clustering program,
 * but in every case we need to read the data in a graph.
 * This class provides the interface for doing so:
 * When a new input format is needed, just implement this interface for that
 * particular input format.
 */
class GraphReader
{
    public:
        /**
         * @brief initalize a reader to read data into a graph
         * @param g the graph in which the data will be read
         */
        GraphReader(AbstractGraph* g) : _graph(g) {}
        /**
         * @brief read file data into graph
         * @return 0 on success
         *         1 on failure
         */
        virtual int readFile(FILE* file) = 0;

        /**
         * @brief standard destructor
         */
        virtual ~GraphReader();
    protected:
        AbstractGraph* _graph;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
