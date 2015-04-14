/**
 * @file GraphReader.hpp
 * @brief class to read a graph from a file
 */
#ifndef CLUSTERER_BACKEND_GRAPH_READER_HPP
#define CLUSTERER_BACKEND_GRAPH_READER_HPP

// standard headers
#include <stdint.h>
#include <vector>
#include <stdio.h>
// external headers

// internal headers
#include "AbstractGraphReader.hpp"

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
 * @brief GraphReader reads a graph with the following format for each line:
 * - vertex1 vertex2 weight
 * - % This is a comment and should not be read in.
 */
class GraphReader : AbstractGraphReader
{
    public:
        /**
        * @brief Initalize a reader to read data into a graph.
        * @param graph The graph in which the data will be read.
        */
        GraphReader(AbstractGraph* graph);

        /**
        * @brief standard destructor
        */
        ~GraphReader();

        /**
        * @brief Read file containing a graph into a graph object.
        * @param filename The filename (which is the fullPathFilename)
        * @return bool Indicating whether or not it read the file in succesfully.
        */
        bool readFile(std::string);
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
