/**
* @file AbstractGraph.hpp
* @brief Graph interface
*/
#ifndef CLUSTERER_BACKEND_ABSTRACT_GRAPH_HPP
#define CLUSTERER_BACKEND_ABSTRACT_GRAPH_HPP

// standard headers
#include <vector>
// external headers

// internal headers
#include "Vertex.hpp"

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
 * @class AbstractGraph
 * @brief Wrapper for Boost Graph Lib
 */

class AbstractGraph
{
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

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
