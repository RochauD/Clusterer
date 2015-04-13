/**
* @file AbstractGraphReader.cpp
* @brief Virtual Destructor for GraphReader
*/
#include "../include/AbstractGraphReader.hpp"

namespace clusterer
{
namespace backend
{

AbstractGraphReader::AbstractGraphReader(AbstractGraph* graph)
{
    this->graph = graph;
}

AbstractGraphReader::~AbstractGraphReader()
{

}

}
}
