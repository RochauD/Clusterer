/**
* @file Graph.cpp
* @brief implementation of Graph subclass of AbstractGraph
*/
#include "../include/Graph.hpp"

namespace clusterer
{
namespace backend
{

Graph::Graph()
{
    no_vertices = 0;
    no_edges = 0;
}

Graph::~Graph()
{

}

uint64_t Graph::getNoVertices() const
{
    return no_vertices;
}


uint64_t Graph::getNoEdges() const
{
    return no_edges;
}

void Graph::addVertex(const Vertex& v)
{
    // only add vertex if it isn't in the graph
    if (vertex_map.find(v.getVNumber()) == vertex_map.end())
    {
        auto u = boost::add_vertex(v.getVNumber(), g);
        vertex_map.insert(std::make_pair(v.getVNumber(), u));
        no_vertices++;
    }
}

void Graph::addEdge(const Vertex& v1, const Vertex& v2)
{
    //property accessor
    auto edgeW = boost::get(boost::edge_weight, g);

    // check if either of the Vertexes was added prior to the graph
    if (vertex_map.find(v1.getVNumber()) == vertex_map.end())
    {
        auto u = boost::add_vertex(v1.getVNumber(), g);
        vertex_map.insert(std::pair<VertexId, Vert>(v1.getVNumber(), u));
        no_vertices++;
    }

    if (vertex_map.find(v2.getVNumber()) == vertex_map.end())
    {
        auto u = boost::add_vertex(v2.getVNumber(), g);
        vertex_map.insert(std::pair<VertexId, Vert>(v2.getVNumber(), u));
        no_vertices++;
    }

    auto u = vertex_map[v1.getVNumber()];
    auto v = vertex_map[v2.getVNumber()];
    // check if edge already exists
    if (boost::edge(u, v, g).second == false)
    {
        boost::add_edge(u, v, g);
        auto e = boost::edge(u, v, g).first;
        edgeW[e] = 0; // set weight to 0 just in case
        no_edges++;
    }
}

void Graph::addEdge(const Vertex& v1, const Vertex& v2, double weight)
{
    //property accessor
    auto edgeW = boost::get(boost::edge_weight, g);

    // check if either of the Vertexes was added prior to the graph
    if (vertex_map.find(v1.getVNumber()) == vertex_map.end())
    {
        auto u = boost::add_vertex(v1.getVNumber(), g);
        vertex_map.insert(std::pair<VertexId, Vert>(v1.getVNumber(), u));
        no_vertices++;
    }

    if (vertex_map.find(v2.getVNumber()) == vertex_map.end())
    {
        auto u = boost::add_vertex(v2.getVNumber(), g);
        vertex_map.insert(std::pair<VertexId, Vert>(v2.getVNumber(), u));
        no_vertices++;
    }

    auto u = vertex_map[v1.getVNumber()];
    auto v = vertex_map[v2.getVNumber()];
    // check if edge already exists
    if (boost::edge(u, v, g).second == false)
    {
        boost::add_edge(u, v, g);
        auto e = boost::edge(u, v, g).first;
        edgeW[e] = weight; // set edge weight
        no_edges++;
    }
}

void Graph::setEdgeWeight(const Vertex& v1, const Vertex& v2, double weight)
{
    auto edgeW = boost::get(boost::edge_weight, g);
    if (existsEdge(v1, v2))
    {
        auto u = vertex_map[v1.getVNumber()];
        auto v = vertex_map[v2.getVNumber()];
        auto e = boost::edge(u, v, g).first;
        edgeW[e] = weight;
    }
}

bool Graph::getEdgeWeight(const Vertex& v1, const Vertex& v2, double* edgeWeight) const
{
    auto edgeW = boost::get(boost::edge_weight, g);
    auto iterVertex1 = vertex_map.find(v1.getVNumber());
    if (iterVertex1 == vertex_map.end())
    {
        return false; // vertex not in the graph
    }
    auto iterVertex2 = vertex_map.find(v2.getVNumber());
    if (iterVertex2 == vertex_map.end())
    {
        return false; // vertex not in the graph
    }

    auto u = iterVertex1->second;
    auto v = iterVertex2->second;
    auto edgeQuery = boost::edge(u, v, g);
    if (edgeQuery.second == false)
    {
        return false;
    }
    auto e = edgeQuery.first;
    *edgeWeight = edgeW[e];
    return true;
}

std::vector<VertexId> Graph::getVertices() const
{
    std::vector<VertexId> verts;

    auto name = boost::get(boost::vertex_name, g);
    for (auto vp = boost::vertices(g); vp.first != vp.second; ++vp.first)
    {
        auto v = *vp.first;
        verts.push_back(name[v]);
    }
    return verts;
}

std::vector<std::pair<VertexId, VertexId>> Graph::getEdges() const
{
    std::vector<std::pair<VertexId, VertexId>> edges;

    auto name = boost::get(boost::vertex_name, g);
    boost::graph_traits<DirectedGraph>::edge_iterator ei;
    boost::graph_traits<DirectedGraph>::edge_iterator ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei)
    {
        edges.push_back(std::make_pair(name[source(*ei, g)], name[target(*ei, g)]));
    }

    return edges;
}

std::vector<std::pair<std::pair<VertexId, VertexId>, double>> Graph::getEdgesAndWeights() const
{
    std::vector<std::pair<std::pair<VertexId,VertexId>, double>> wedges;

    auto name = boost::get(boost::vertex_name, g);
    auto edgeW = boost::get(boost::edge_weight, g);

    boost::graph_traits<DirectedGraph>::edge_iterator ei;
    boost::graph_traits<DirectedGraph>::edge_iterator ei_end;
    for (tie(ei,ei_end) = boost::edges(g); ei != ei_end; ++ei)
    {
        auto u = source(*ei,g);
        auto v = target(*ei,g);
        auto e = boost::edge(u,v,g).first;
        wedges.push_back(std::make_pair(std::make_pair(name[source(*ei,g)],name[target(*ei,g)]),edgeW[e]));
    }

    return wedges;
}

std::vector<VertexId> Graph::getNeighbors(const Vertex& v) const
{
    std::vector<VertexId> vec;

    auto vertexIter = vertex_map.find(v.getVNumber());
    if (vertexIter == vertex_map.end())
    {
        // no such Vertex v in the graph
        return vec;
    }
    auto u = vertexIter->second;
    auto neighbors = boost::adjacent_vertices(u,g);
    auto name = boost::get(boost::vertex_name, g);

    for (; neighbors.first != neighbors.second; ++neighbors.first)
    {
        vec.push_back(name[*neighbors.first]);
    }
    return vec;
}

bool Graph::existsEdge(const Vertex& v1, const Vertex& v2) const
{
    auto iterVertex1 = vertex_map.find(v1.getVNumber());
    if (iterVertex1 == vertex_map.end())
    {
        return false; // vertex not in the graph
    }
    auto iterVertex2 = vertex_map.find(v2.getVNumber());
    if (iterVertex2 == vertex_map.end())
    {
        return false; // vertex not in the graph
    }
    auto u = iterVertex1->second;
    auto v = iterVertex2->second;
    auto edgeQuery = boost::edge(u, v, g);

    return (edgeQuery.second == true);
}

}
}
