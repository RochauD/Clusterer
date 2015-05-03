/**
* @file MovieLensGraphReader.hpp
* @brief class to read a graph from a file
*/
#ifndef CLUSTERER_BACKEND_MOVIE_LENS_GRAPH_READER_HPP
#define CLUSTERER_BACKEND_MOVIE_LENS_GRAPH_READER_HPP

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
* @class MovieLensGraphReader
* @brief MovieLensGraphReader reads a graph in the movie lens format.
*/
class MovieLensGraphReader : AbstractGraphReader
{
    public:
        /**
        * @brief Initalize a reader to read data into a graph.
        * @param graph The graph in which the data will be read.
        */
        MovieLensGraphReader(AbstractGraph* graph);

        /**
        * @brief standard destructor
        */
        ~MovieLensGraphReader();

        /**
        * @brief Read file containing a graph into a graph object.
        * @param fullPathName The filename (which is the fullPathFilename)
        * @return bool Indicating whether or not it read the file in succesfully.
        */
        bool readFile(std::string fullPathName);
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
