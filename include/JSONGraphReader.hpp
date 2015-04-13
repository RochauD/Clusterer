/**
 * @file JSONGraphReader.hpp
 * @brief class to read a graph from a file using the JSON format
 */
#ifndef CLUSTERER_BACKEND_JSON_GRAPH_READER_HPP
#define CLUSTERER_BACKEND_JSON_GRAPH_READER_HPP

// standard headers
#include <stdint.h>
#include <stdio.h>
// external headers

// internal headers
#include "AbstractGraph.hpp"


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
 * @class JSONGraphReader
 * @brief Implementation of the GraphReader interface which accepts only
 * JSON-formatted files
 */
class JSONGraphReader
{
    public:
        /**
         * @brief initalize a reader to read data into a graph
         * @param g the graph in which the data will be read
         */
        JSONGraphReader(AbstractGraph* g);
        /**
         * @brief read file data into graph
         * @return 0 on success
         *         1 on failure
         */
        int readFile(FILE* file);
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
