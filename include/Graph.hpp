/**
* @file Graph.hpp
* @brief Implementation of AbstractGraph interface
*/
#ifndef CLUSTERER_BACKEND_GRAPH_HPP
#define CLUSTERER_BACKEND_GRAPH_HPP

// standard headers
#include <utility>
#include <vector>
#include <map>
#include <cstdint>
// external headers
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
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

typedef boost::property<boost::vertex_name_t, VertexId> VertexName;
typedef boost::property<boost::edge_weight_t, double> EdgeWeight;

// an adjacency_list model
typedef boost::adjacency_list<boost::vecS, boost::vecS,
        boost::directedS, VertexName,
        EdgeWeight> DirectedGraph;

typedef boost::graph_traits<DirectedGraph>::vertex_descriptor Vert;
typedef boost::graph_traits<DirectedGraph>::edge_descriptor Edge;

/**
* @class Graph
* @brief Handles the graph representation of the input data
* @details The class Graph build on top of Boost Graph Library
* provides methods to access relevant structures in the given
* data such as vertices, edge connections and the neighbors vertex
*/
class Graph : public virtual clusterer::backend::AbstractGraph
{
    public:
        /**
        * @brief empty Constructor for the Graph
        */
        Graph();

        /**
        * @brief destructor for the class Graph
        */
        ~Graph();

        /**
        * @brief getter for the current number of vertices added in the graph
        * @return number of vertices
        */
        uint64_t getNoVertices() const;

        /**
        * @brief getter for the current number of edges in the graph
        * @return number of edges
        */
        uint64_t getNoEdges() const;

        /**
        * @brief getter for the offset
        * @return offset
        */
        uint64_t getOffset() const;

        /**
        * @brief assign a node in the graph to a Vertex object
        * @param v constant reference to a Vertex object
        * @return void
        */
        void addVertex(const Vertex& v);

        /**
        * @brief assign an edge in the graph as a connection between 2 Vertex objects
        * @param v1 constant reference to first Vertex object
        * @param v2 constant reference to second Vertex object
        * @return void
        */
        void addEdge(const Vertex& v1, const Vertex& v2);

        /**
        * @brief assign an edge in the graph between 2 Vertex objects and its weight
        * @param v1 constant reference to first Vertex object
        * @param v2 constant reference to second Vertex object
        * @param weight last parameter the weight to be assigned to the edge
        * @return void
        */
        void addEdge(const Vertex& v1, const Vertex& v2, double weight);

        /**
        * @brief set the weight of an edge if it exists
        * @param v1 constant reference to first Vertex object
        * @param v2 constant reference to second Vertex object
        * @param weight double value for the weight
        * @return void
        */
        void setEdgeWeight(const Vertex& v1, const Vertex& v2, double weight);

        /**
        * @brief Returns the weight of an edge.
        * @param[in] v1 Constant reference to first Vertex object
        * @param[in] v2 Constant reference to second Vertex object
        * @param[out] edgeWeight The weight of the edge
        * @bool True if edge exists, false if edge does not exist and therefore cannot have
        * a weight
        */
        bool getEdgeWeight(const Vertex& v1, const Vertex& v2, double* edgeWeight) const;

        /**
        * @brief getter to get the offsetted vertex name
        * @return the value described 
        */
        uint64_t getVertexOffsetName(const Vertex& v) const;

        /**
        * @brief getter for the node representations in the graph
        * @return vector of VertexId, each VertexId partaining to a Vertex object
        */
        std::vector<VertexId> getVertices() const;

        /**
        * @brief getter for the edges in the graph
        * @return vector of pairs of type <VertexId,VertexId>
        */
        std::vector<std::pair<VertexId, VertexId>> getEdges() const;

        /**
        * @brief getter for the edges in the graph and their respective weights
        * @return vector of pairs <pair<VertexId,VertexId>, double>
        * pair of node indeces and their respective weight
        */
        std::vector<std::pair<std::pair<VertexId, VertexId>, double>> getEdgesAndWeights() const;

        /**
        * @brief getter for the neighbor Vertexes of a given Vertex object
        * @return a vector of VertexId
        */
        std::vector<VertexId> getNeighbors(const Vertex&) const;

        /**
        * @brief check if edge exists
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @return true if it does, false if it doesn't figures...
        */
        bool existsEdge(const Vertex&, const Vertex&) const;


    protected:
        /**
        * @var g
        * @brief local representation of the graph created using BGL
        */
        DirectedGraph g;
    private:
        /**
        * @var no_vertices
        * @brief keeping track of the number of vertices in the graph
        */
        uint64_t no_vertices;

        /**
        * @var no_edges
        * @brief keeping track of the number of edges in the graph
        */
        uint64_t no_edges;

        /**
        * @var vertex_map
        * @brief a map between VertexId, representative of a Vertex object,
        * and the vertex descriptor in the graph corresponding to a node in the
        * graph.
        */
        std::map<VertexId,Vert> vertex_map;

        /**
        * @var OFFSET
        * @brief will map each vertex id starting from 0
        */
        uint64_t OFFSET;

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
