/**
* @file Graph.hpp
* @brief Subclass of AbstractGraph interface
*/
#ifndef CLUSTERER_BACKEND_GRAPH_HPP
#define CLUSTERER_BACKEND_GRAPH_HPP

// standard headers
#include <utility> //maybe pair
#include <string>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
// external headers

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

class Graph : public virtual AbstractGraph
{
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

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif // GRAPH_HPP
