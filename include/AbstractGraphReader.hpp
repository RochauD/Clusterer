/**
* @file AbstractGraphReader.hpp
* @brief Abstract class representing an interface for graph reader classes.
*/
#ifndef CLUSTERER_BACKEND_ABSTRACT_GRAPH_READER_HPP
#define CLUSTERER_BACKEND_ABSTRACT_GRAPH_READER_HPP

// standard headers
#include <string>
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
* @class AbstractGraphReader
* @brief Interface to read a file containing a graph into an AbstractGraph.
* @details There might be many possible input formats to the social clustering program,
* but in every case we need to read the data in a graph.
* This class provides the interface for doing so:
* When a new input format is needed, just implement this interface for that
* particular input format.
*/
class AbstractGraphReader
{
    public:
        /**
        * @brief Initalize a reader to read data into a graph.
        * @param graph The graph in which the data will be read.
        */
        AbstractGraphReader(AbstractGraph* graph);

        /**
        * @brief standard destructor
        */
        virtual ~AbstractGraphReader();

        /**
        * @brief Read file containing a graph into a graph object.
        * @param filename The filename (which is the fullPathFilename)
        * @return bool Indicating whether or not it read the file in succesfully.
        */
        virtual bool readFile(std::string filename) = 0;

    protected:
        /**
        * @var graph
        * @brief Pointer to the Graph object which contains the information read
        * from file in a graph representation.
        */
        AbstractGraph* graph;
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
