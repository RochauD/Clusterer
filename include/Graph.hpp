/**
  * @brief  subclass of AbstractGraph interface
  *
  * @file Graph.hpp
  */

#ifndef GRAPH_HPP
#define GRAPH_HPP

// c++ libraries
#include <utility> //maybe pair
#include <vector>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

// local headers
#include "AbstractGraph.hpp"

namespace common
{
namespace types
{

using namespace boost;

typedef property<vertex_name_t,VertexId> VertexName;
typedef property<edge_weight_t,double> EdgeWeight;

// an adjacency_list model
typedef boost::adjacency_list<boost::vecS, boost::vecS,
                              boost::directedS, VertexName,
                              EdgeWeight> DirectedGraph;

typedef graph_traits<DirectedGraph>::vertex_descriptor Vert;
typedef graph_traits<DirectedGraph>::edge_descriptor Edge;

/**
* @class Graph
* @brief Handles the graph representation of the input data
* @details The class Graph build on top of Boost Graph Library
* provides methods to access relevant structures in the given
* data such as vertices, edge connections and the neighbors vertex
*/
class Graph : public virtual common::types::AbstractGraph{
    public:
        /**
        * @brief empty Constructor for the Graph
        */
        Graph();
        /**
        * @brief getter for the current number of vertices added in the graph
        * @return number of vertices
        */
        int getNoVertices();
        /**
        * @brief getter for the current number of edges in the graph
        * @return number of edges
        */
        int getNoEdges();
        /**
        * @brief assign a node in the graph to a Vertex object
        * @param reference to a Vertex object
        * @return void
        */
        void addVertex(const Vertex&);
        /**
        * @brief assign an edge in the graph as a connection between 2 Vertex objects
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @return void
        */
        void addEdge(const Vertex&, const Vertex&);
        /**
        * @brief assign an edge in the graph between 2 Vertex objects and its weight
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @param last parameter the weight to be assigned to the edge
        * @return void
        */
        void addEdge(const Vertex&, const Vertex&, double);
        /**
        * @brief set the weight of an edge if it exists
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @param double value for the weight
        * @return void
        */
        void setEdgeWeight(const Vertex&, const Vertex&, double);
        /**
        * @brief get the weight of an edge
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @double the value of the edge weight
        */
        double getEdgeWeight(const Vertex&, const Vertex&);
        /**
        * @brief getter for the node representations in the graph
        * @return vector of VertexId, each VertexId partaining to a Vertex object
        */
        std::vector<VertexId> getVertices();
        /**
        * @brief getter for the edges in the graph
        * @return vector of pairs of type <VertexId,VertexId> 
        */
        std::vector<std::pair<VertexId,VertexId>> getEdges();
        /**
        * @brief getter for the edges in the graph and their respective weights
        * @return vector of pairs <pair<VertexId,VertexId>, double>
        * pair of node indeces and their respective weight  
        */
        std::vector<std::pair<std::pair<VertexId,VertexId>,double>> getEdgesAndWeights();
        /**
        * @brief getter for the neighbor Vertexes of a given Vertex object
        * @return a vector of VertexId
        */
        std::vector<VertexId> getNeighbors(const Vertex&);
        /**
        * @brief check if edge exists
        * @param constant reference to first Vertex object
        * @param constant reference to second Vertex object
        * @return true if it does, false if it doesn't figures...
        */
        bool existsEdge(const Vertex&, const Vertex&);
        /**
        * @brief destructor for the class Graph
        */
        virtual ~Graph();
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
        int no_vertices;
        /**
        * @var no_edges
        * @brief keeping track of the number of edges in the graph
        */
        int no_edges;
        /**
        * @var vertex_map
        * @brief a map between VertexId, representative of a Vertex object,
        * and the vertex descriptor in the graph corresponding to a node in the
        * graph.
        */
        std::map<VertexId,Vert> vertex_map;
};
} //namespace types
} //namespace common

#endif // GRAPH_HPP
