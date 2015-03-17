/**
  * @brief  Graph interface
  *
  * @file AbstractGraph.hpp
  * @author Radu Hambasan <r.hambasan@jacobs-university.de>
  * @date   27 Feb 2015
  *
  */

#ifndef _COMMON_TYPES_ABSTRACTGRAPH_HPP
#define _COMMON_TYPES_ABSTRACTGRAPH_HPP


// Standard libraries
#include <vector>

// local headers
#include "Vertex.hpp"

namespace common {
namespace types {

/**
 * @class AbstractGraph
 * @brief Wrapper for Boost Graph Lib
 */

class AbstractGraph {
 public:
     /*
      * @brief initialize an empty graph
      */
     AbstractGraph();
     virtual ~AbstractGraph() = 0;
     /**
      * @brief get the vertices in the graph
      * @return a vector containing the vertices in the graph
      */
     virtual std::vector<VertexId> getVertices() = 0; 
    /** 
     * @brief add a vertex to this graph
     * @param vert the vertex to be added
     */
    virtual void addVertex(const Vertex& vert) = 0;
    /** 
     * @brief create an edge between to vertices
     * @param vert1 an id representing the source vertex of the edge
     * @param vert2 an id representing the destination vertex of the edge
     */
    virtual void addEdge(const Vertex& vertId1, const Vertex& vertId2) = 0;
};

}  // namespace types
}  // namespace common

#endif  // _COMMON_TYPES_ABSTRACTGRAPH_HPP
