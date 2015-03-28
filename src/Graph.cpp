/**
 * @brief implementation of Graph subclass
 * @file Graph.cpp
 * @todo add logging
 */

#include "../include/Graph.hpp"

#include <iostream> // remove this after logging

namespace clusterer
{
namespace backend
{

Graph::Graph(int No_vert)
{
    no_vertices = No_vert;
    no_edges = 0;
    vertices = new Vert[no_vertices];
}

Graph::~Graph()
{
    delete[] vertices;
}

void Graph::addVertex(const Vertex& v)
{
    if (v.getVNumber() > no_vertices)
    {
        std::cout<<"Illegal Vertex number tried to be passed\n";
    }
    else
    {
        for (int i = boost::num_vertices(g)+1; i <= v.getVNumber(); i++)
        { boost::add_vertex(g); }
    }
}

void Graph::addEdge(const Vertex& v1, const Vertex& v2)
{
    //property accessor
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = boost::get(edge_weight, g);

    /* not used in this context
    typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);*/

    Edge e;
    bool found;
    Vert u,v;

    if (v1.getVNumber() > no_vertices || v2.getVNumber() > no_vertices)
    {
        std::cout<<"Illegal Vertices numbers in Graph::addEdge\n";
    }
    else
    {
        boost::add_edge(v1.getVNumber(),v2.getVNumber(),g);
        u = boost::vertex(v1.getVNumber(),g);
        v = boost::vertex(v2.getVNumber(),g);
        boost::tie(e,found) = boost::edge(u,v,g);
        edgeW[e] = 0;

        /*
        cout<<"weight is "<<edgeW[e]<<"\n";
        cout<<"index of u:"<<index[u]<<" index of v:"<<index[v]<<"\n";
        cout<<"index of u:"<<index[vertices[v1.getVNumber()]]<<" index of v:"<<index[vertices[v2.getVNumber()]]<<"\n";
        */
        no_edges++;
    }
}

void Graph::addEdge(const Vertex& v1, const Vertex& v2, int weight)
{
    //property accessor
    /* not used in this context (for now)
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = get(edge_weight, g);

    typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);*/

    Edge e;
    bool found;
    Vert u,v;

    if (v1.getVNumber() > no_vertices || v2.getVNumber() > no_vertices)
    {
        std::cout<<"Illegal Vertices numbers in Graph::addEdge\n";
    }
    else
    {

        boost::add_edge(v1.getVNumber(),v2.getVNumber(),weight,g);
        u = vertex(v1.getVNumber(),g);
        v = vertex(v2.getVNumber(),g);
        boost::tie(e,found) = boost::edge(u,v,g);
        /*
        cout<<"weight is "<<edgeW[e]<<"\n";
        cout<<"index of u:"<<index[u]<<" index of v:"<<index[v]<<"\n";
        */
        no_edges++;
    }
}

int Graph::getNoEdges()
{
    return no_edges;
}

int Graph::getNoVertices()
{
    return no_vertices;
}

std::vector<VertexId> Graph::getVertices()
{
    std::vector<VertexId> verts;

    typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index,g);


    typedef graph_traits<DirectedGraph>::vertex_iterator v_iter;
    std::pair<v_iter, v_iter> vp;

    for (vp = boost::vertices(g); vp.first != vp.second; ++vp.first)
    {
        Vert v = *vp.first;
        if (index[v] != 0)
        {
            verts.push_back(index[v]);
        }
        //if(index[v] == 0){ // probably there won't be a vertex 0
        //std::cout<<"index[v] to be deleted: "<<index[v]<<"\n";
        //boost::remove_vertex(v,g);
        //} else {
        // std::cout << index[v] << " "<<vname[v]<<"\n";
        // verts.push_back(index[v]);
        //}
    }

    return verts;
}

std::vector<std::pair<VertexId,VertexId>> Graph::getEdges()
{
    std::vector<std::pair<VertexId,VertexId>> edges;

    typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    graph_traits<DirectedGraph>::edge_iterator ei, ei_end;
    for (tie(ei,ei_end) = boost::edges(g); ei != ei_end; ++ei)
    {
        //std::cout<<"("<<index[source(*ei,g)]<<","<<index[target(*ei,g)]<<")";
        edges.push_back(std::make_pair(index[source(*ei,g)],index[target(*ei,g)]));
    }

    return edges;
}

std::vector<VertexId> Graph::getNeighbors(const Vertex& v)
{
    std::vector<VertexId> vec;
    typedef boost::graph_traits<DirectedGraph>::adjacency_iterator adj_it;

    typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);


    std::pair<adj_it,adj_it> neighbors = boost::adjacent_vertices(vertex(v.getVNumber(),g),g);

    for (; neighbors.first != neighbors.second; ++neighbors.first)
    {
        vec.push_back(index[*neighbors.first]);
    }

    /* second method
    graph_traits<DirectedGraph>::edge_iterator ei, ei_end;
    for(tie(ei,ei_end) = boost::edges(g); ei != ei_end; ++ei){
        //std::cout<<"("<<index[source(*ei,g)]<<","<<index[target(*ei,g)]<<")";
        if(index[source(*ei,g)] == v.getVNumber()){
            std::cout<<""<<index[target(*ei,g)];
            vec.push_back(index[target(*ei,g)]);
        }
    }*/
    return vec;
}

}
}
