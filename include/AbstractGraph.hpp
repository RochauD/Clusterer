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

        virtual int getNoVertices() const = 0;
        /**
        * @brief getter for the current number of edges in the graph
        * @return number of edges
        */
        virtual int getNoEdges() const = 0;
        /**
        * @brief assign a node in the graph to a Vertex object
        * @param reference to a Vertex object
        * @return void
        */
        virtual void addVertex(const Vertex&) = 0;
        /**
        * @brief assign an edge in the graph as a connection between 2 Vertex objects
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @return void
        */
        virtual void addEdge(const Vertex&, const Vertex&) = 0;
        /**
        * @brief assign an edge in the graph between 2 Vertex objects and its weight
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @param last parameter the weight to be assigned to the edge
        * @return void
        */
        virtual void addEdge(const Vertex&, const Vertex&, double) = 0;
        /**
        * @brief set the weight of an edge if it exists
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @param double value for the weight
        * @return void
        */
        virtual void setEdgeWeight(const Vertex&, const Vertex&, double) = 0;
        /**
        * @brief get the weight of an edge
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @double the value of the edge weight
        */
        virtual double getEdgeWeight(const Vertex&, const Vertex&) = 0;
        /**
        * @brief getter for the node representations in the graph
        * @return vector of VertexId, each VertexId partaining to a Vertex object
        */
        virtual std::vector<VertexId> getVertices() = 0;
        /**
        * @brief getter for the edges in the graph
        * @return vector of pairs of type <VertexId,VertexId>
        */
        virtual std::vector<std::pair<VertexId, VertexId>> getEdges() = 0;
        /**
        * @brief getter for the edges in the graph and their respective weights
        * @return vector of pairs <pair<VertexId,VertexId>, double>
        * pair of node indeces and their respective weight
        */
        virtual std::vector<std::pair<std::pair<VertexId, VertexId>, double>> getEdgesAndWeights() const = 0;
        /**
        * @brief getter for the neighbor Vertexes of a given Vertex object
        * @return a vector of VertexId
        */
        virtual std::vector<VertexId> getNeighbors(const Vertex&) = 0;
        /**
        * @brief check if edge exists
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @return true if it does, false if it doesn't figures...
        */
        virtual bool existsEdge(const Vertex&, const Vertex&) = 0;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
