/**
  * @brief  subclass of AbstractGraph interface
  *
  * @file Graph.hpp
  */

#ifndef GRAPH_HPP
#define GRAPH_HPP

// c++ libraries
#include <utility> //maybe pair
#include <string>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

// local headers
#include "AbstractGraph.hpp"

namespace common
{
namespace types
{

using namespace boost;

typedef property<vertex_name_t,std::string> VertexName;
typedef property<edge_weight_t,int> EdgeWeight;

// an adjacency_list model
typedef boost::adjacency_list<boost::vecS, boost::vecS,
                              boost::directedS, VertexName,
                              EdgeWeight> DirectedGraph;

typedef graph_traits<DirectedGraph>::vertex_descriptor Vert;
typedef graph_traits<DirectedGraph>::edge_descriptor Edge;
//typedef std::pair<int, int> edgeG;

class Graph : public virtual common::types::AbstractGraph{
    public:
        //Graph();
        Graph(int);
        int getNoVertices();
        int getNoEdges();
        void addVertex(const Vertex&);
        void addEdge(const Vertex&, const Vertex&);
        void addEdge(const Vertex&, const Vertex&, int);
        std::vector<VertexId> getVertices();
        std::vector<std::pair<VertexId,VertexId>> getEdges();
        std::vector<VertexId> getNeighbors(const Vertex&);
        virtual ~Graph();
    protected:
        DirectedGraph g;
        Vert* vertices;
    private:
        int no_vertices;
        int no_edges;
};
} //namespace types
} //namespace common

#endif // GRAPH_HPP
