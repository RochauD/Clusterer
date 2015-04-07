/**
* @brief implementation of Graph subclass of AbstractGraph
* @file Graph.cpp
*/

// local headers
#include "../include/Graph.hpp"

namespace clusterer
{
namespace backend
{

/*Graph::Graph(int No_vert){
    no_vertices = No_vert;
    no_edges = 0;
}*/

Graph::Graph(){
    no_vertices = 0;
    no_edges = 0;
}

Graph::~Graph(){
}

bool Graph::existsEdge(const Vertex& v1, const Vertex& v2){
    if(vertex_map.find(v1.getVNumber()) == vertex_map.end()){
        return false; // vertex not in the graph
    }
    if(vertex_map.find(v2.getVNumber()) == vertex_map.end()){
        return false; // vertex not in the graph
    }
    Vert u,v;
    u = vertex_map[v1.getVNumber()];
    v = vertex_map[v2.getVNumber()];
    return boost::edge(u,v,g).second == true;
}

void Graph::setEdgeWeight(const Vertex& v1, const Vertex& v2, double weight){
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = boost::get(edge_weight, g);
    if(existsEdge(v1,v2)) {
        Vert u,v;
        Edge e;
        u = vertex_map[v1.getVNumber()];
        v = vertex_map[v2.getVNumber()];
        e = boost::edge(u,v,g).first;
        edgeW[e] = weight;
    } 
}

void Graph::addVertex(const Vertex& v){
    // only add vertex if it isn't in the graph
    if(vertex_map.find(v.getVNumber()) == vertex_map.end()){
        Vert u = boost::add_vertex(v.getVNumber(),g);
        vertex_map.insert(std::pair<VertexId,Vert>(v.getVNumber(),u));
        no_vertices++;
    }
}

void Graph::addEdge(const Vertex& v1, const Vertex& v2){
    //property accessor
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = boost::get(edge_weight, g);

    Edge e;
    Vert u,v;

    // check if either of the Vertexes was added prior to the graph
    if(vertex_map.find(v1.getVNumber()) == vertex_map.end()){
        Vert u = boost::add_vertex(v1.getVNumber(),g);
        vertex_map.insert(std::pair<VertexId,Vert>(v1.getVNumber(),u));
        no_vertices++;
    }

    if(vertex_map.find(v2.getVNumber()) == vertex_map.end()){
        Vert u = boost::add_vertex(v2.getVNumber(),g);
        vertex_map.insert(std::pair<VertexId,Vert>(v2.getVNumber(),u));
        no_vertices++;
    }

    u = vertex_map[v1.getVNumber()];
    v = vertex_map[v2.getVNumber()];
    // check if edge already exists
    if(boost::edge(u,v,g).second == false){
        boost::add_edge(u,v,g);
        e = boost::edge(u,v,g).first;
        edgeW[e] = 0; // set weight to 0 just in case
        no_edges++;
    }

}

void Graph::addEdge(const Vertex& v1, const Vertex& v2, double weight){
    //property accessor
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = boost::get(edge_weight, g);

    Edge e;
    Vert u,v;

    // check if either of the Vertexes was added prior to the graph
    if(vertex_map.find(v1.getVNumber()) == vertex_map.end()){
        Vert u = boost::add_vertex(v1.getVNumber(),g);
        vertex_map.insert(std::pair<VertexId,Vert>(v1.getVNumber(),u));
        no_vertices++;
    }

    if(vertex_map.find(v2.getVNumber()) == vertex_map.end()){
        Vert u = boost::add_vertex(v2.getVNumber(),g);
        vertex_map.insert(std::pair<VertexId,Vert>(v2.getVNumber(),u));
        no_vertices++;
    }

    u = vertex_map[v1.getVNumber()];
    v = vertex_map[v2.getVNumber()];
    // check if edge already exists
    if(boost::edge(u,v,g).second == false){
        boost::add_edge(u,v,g);
        e = boost::edge(u,v,g).first;
        edgeW[e] = weight; // set edge weight
        no_edges++;
    }
}

int Graph::getNoEdges(){
    return no_edges;
}

int Graph::getNoVertices(){
    return no_vertices;
}

double Graph::getEdgeWeight(const Vertex& v1, const Vertex& v2){
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = boost::get(edge_weight, g);
    if(existsEdge(v1,v2)) {
        Vert u,v;
        Edge e;
        u = vertex_map[v1.getVNumber()];
        v = vertex_map[v2.getVNumber()];
        e = boost::edge(u,v,g).first;
        return edgeW[e];
    }
    return -1; // if edge does not exist
}

std::vector<VertexId> Graph::getVertices(){
    std::vector<VertexId> verts;

    /*typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index,g);*/ // index not needed here
    typedef property_map<DirectedGraph, vertex_name_t>::type NameMap;
    NameMap name = get(vertex_name, g);

    typedef graph_traits<DirectedGraph>::vertex_iterator v_iter;
    std::pair<v_iter, v_iter> vp;

    for(vp = boost::vertices(g); vp.first != vp.second; ++vp.first){
        Vert v = *vp.first;
        verts.push_back(name[v]);
    }

    return verts;
}

std::vector<std::pair<VertexId,VertexId>> Graph::getEdges(){
    std::vector<std::pair<VertexId,VertexId>> edges;

    typedef property_map<DirectedGraph, vertex_name_t>::type NameMap;
    NameMap name = get(vertex_name, g);

    graph_traits<DirectedGraph>::edge_iterator ei, ei_end;
    for(tie(ei,ei_end) = boost::edges(g); ei != ei_end; ++ei){
        edges.push_back(std::make_pair(name[source(*ei,g)],name[target(*ei,g)]));
    }

    return edges;
}

std::vector<std::pair<std::pair<VertexId,VertexId>,double>> Graph::getEdgesAndWeights(){
    std::vector<std::pair<std::pair<VertexId,VertexId>,double>> wedges;

    typedef property_map<DirectedGraph, vertex_name_t>::type NameMap;
    NameMap name = get(vertex_name, g);
    typedef property_map<DirectedGraph,edge_weight_t>::type EdgeW;
    EdgeW edgeW = boost::get(edge_weight, g);

    Edge e;
    Vert u,v;
    graph_traits<DirectedGraph>::edge_iterator ei, ei_end;
    for(tie(ei,ei_end) = boost::edges(g); ei != ei_end; ++ei){
        u = source(*ei,g);
        v = target(*ei,g);
        e = boost::edge(u,v,g).first;
        wedges.push_back(std::make_pair(std::make_pair(name[source(*ei,g)],name[target(*ei,g)]),edgeW[e]));
    }

    return wedges;
}


std::vector<VertexId> Graph::getNeighbors(const Vertex& v){
    std::vector<VertexId> vec;
    typedef boost::graph_traits<DirectedGraph>::adjacency_iterator adj_it;

    /*typedef property_map<DirectedGraph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);*/

    typedef property_map<DirectedGraph, vertex_name_t>::type NameMap;
    NameMap name = get(vertex_name, g);

    Vert u;
    if(vertex_map.find(v.getVNumber()) == vertex_map.end()){
        // no such Vertex v in the graph
        return vec; 
    } 
    u = vertex_map[v.getVNumber()];

    std::pair<adj_it,adj_it> neighbors = boost::adjacent_vertices(u,g);

    for(; neighbors.first != neighbors.second; ++neighbors.first){
        vec.push_back(name[*neighbors.first]);
    }
 
    return vec;
}

} //namespace clusterer
} // namespace backend
