/**
  * @file GraphReader.hpp
  * @brief class to read a graph from a file
  */
#ifndef _BACKEND_READER_GRAPHREADER_HPP
#define _BACKEND_READER_GRAPHREADER_HPP

//Standard libraries
#include <stdint.h>
#include <stdio.h>

//Own libraries
#include "../include/AbstractGraph.hpp"

namespace backend
{
namespace reader
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
    GraphReader(common::types::AbstractGraph* g) : _graph(g) {}
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
    common::types::AbstractGraph* _graph;
};

}  // namespace reader
}  // namespace backend

#endif  // _BACKEND_READER_GRAPHREADER_HPP

