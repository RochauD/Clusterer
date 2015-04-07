#include <iostream>
#include <cstdlib>
#include "include/Vertex.hpp"
#include "include/AbstractGraph.hpp"
#include "include/Graph.hpp"
#include "include/GraphReader2.hpp"

using namespace clusterer::backend;

/**
* A second option for GraphReader following the structure
* in the initial class diagram in more detail
*/

int main(){

    Graph *g = new Graph();
    GraphReader2 gr(g);
    gr.readFile("test_files/out.ucidata-zachary");
    // can be replaced with "test_files/out.ucidata-zachary"
    std::cout<<"File name: "<<gr.getFileName()<<"\n";

    std::cout<<"number of edges: "<<g->getNoEdges()<<"\n";
    std::cout<<"number of vertices: "<<g->getNoVertices()<<"\n";

    std::vector<std::pair<VertexId,VertexId>> edges = g->getEdges();

    std::cout<<"edges: \n";
    std::vector<std::pair<VertexId,VertexId>>::iterator it;
    for(it = edges.begin(); it != edges.end(); ++it){
         std::cout<<(*it).first<<" "<<(*it).second<<"\n";
    }

    std::cout<<"vertices: \n";
    std::vector<VertexId> vec = g->getVertices();

    std::vector<VertexId>::iterator it2;
    for(auto t:vec){
       std::cout<<t<<" ";
    }
    std::cout<<"\n";

    std::vector<std::pair<std::pair<VertexId,VertexId>,double>> wedges = g->getEdgesAndWeights();

    std::cout<<"edges: \n";
    std::vector<std::pair<std::pair<VertexId,VertexId>,double>>::iterator wit;
    for(wit = wedges.begin(); wit != wedges.end(); ++wit){
         std::cout<<(*wit).first.first<<" "<<(*wit).first.second;
         std::cout<<" with weight: "<<(*wit).second<<"\n";
    }
    
    /*
    Vertex* vp = gr.getVertex(23);
    std::cout<<"vertex id: "<<vp->getVNumber()<<"\n";*/

    delete g;
	return 0;
}