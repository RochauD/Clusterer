/**
  * @file JSONGraphReader.hpp
  * @brief class to read a graph from a file using the JSON format
  */
#ifndef _BACKEND_READER_JSONGRAPHREADER_HPP
#define _BACKEND_READER_JSONGRAPHREADER_HPP

//Standard libraries
#include <stdint.h>
#include <stdio.h>

//Own libraries
#include "AbstractGraph.hpp"
#include "GraphReader.hpp"

namespace backend
{
namespace reader
{

/**
 * @class JSONGraphReader
 * @brief Implementation of the GraphReader interface which accepts only
 * JSON-formatted files
 */
class JSONGraphReader : public GraphReader
{
public:
    /**
     * @brief initalize a reader to read data into a graph
     * @param g the graph in which the data will be read
     */
    JSONGraphReader(common::types::AbstractGraph* g);
    /**
     * @brief read file data into graph
     * @return 0 on success
     *         1 on failure
     */
    int readFile(FILE* file);
};

}  // namespace reader
}  // namespace backend

#endif  // _BACKEND_READER_GRAPHREADER_HPP

