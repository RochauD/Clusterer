#include <iostream>
#include "include/Vertex.hpp"
#include "include/AbstractGraph.hpp"
#include "include/Graph.hpp"
#include "include/GraphReader.hpp"

using namespace clusterer::backend;

/**
* Integrated testing of Graph and GraphReader
*/

int main(){
    
    GraphReader g1("test_files/Graph2.txt");
    g1.readFile();
   // std::vector<std::pair<uint64_t,uint64_t> > g1_Edges;
    std::vector<VertexId> total_vertices;
    std::vector<std::pair<std::pair<VertexId,VertexId>, VertexId> > g1_weights;
    //g1_Edges = g1.getEdges();
    //g1.printEdges(g1_Edges);
    g1_weights = g1.getEdgesWeight();
    g1.printEdgesWeight(g1_weights);
    
    std::cout<<"\n-------------------\n\n";

    const int NO_V = 10;
    Vertex v[NO_V];
    for(int i = 0; i < NO_V; i++){
        v[i].setVNumber(i);
        std::cout<<v[i].getVNumber()<<" ";
    }
    std::cout<<"\n";

    Graph gr;
    std::cout<<"number of edges: "<<gr.getNoEdges()<<"\n";
    std::cout<<"number of vertices: "<<gr.getNoVertices()<<"\n";

    gr.addEdge(v[2],v[3]);
    gr.addEdge(v[1],v[5]);
    gr.addEdge(v[7],v[4]);
    gr.addEdge(v[7],v[4]);
    gr.addEdge(v[1],v[3],2.45);
    gr.addEdge(v[6],v[8]);
    gr.addEdge(v[5],v[7]);
    gr.addEdge(v[2],v[4]);

    std::cout<<"edge: 2 -- 3 = "<<gr.existsEdge(v[2],v[3])<<"\n";
    std::cout<<"edge: 2 -- 3 weight: "<<gr.getEdgeWeight(v[2],v[3])<<"\n";
    gr.setEdgeWeight(v[2],v[3],1.45);
    std::cout<<"edge: 2 -- 3 new weight: "<<gr.getEdgeWeight(v[2],v[3])<<"\n";
    std::cout<<"edge: 2 -- 7 = "<<gr.existsEdge(v[2],v[7])<<"\n";
    std::cout<<"edge: 2 -- 7 weight: "<<gr.getEdgeWeight(v[2],v[7])<<"\n";
    std::cout<<"edge: 1 -- 3 = "<<gr.existsEdge(v[1],v[3])<<"\n";
    std::cout<<"edge: 1 -- 3 weight: "<<gr.getEdgeWeight(v[1],v[3])<<"\n";

    std::vector<std::pair<VertexId,VertexId>> edges = gr.getEdges();

    std::cout<<"edges: \n";
    std::vector<std::pair<VertexId,VertexId>>::iterator it;
    for(it = edges.begin(); it != edges.end(); ++it){
         std::cout<<(*it).first<<" "<<(*it).second<<"\n";
    }

    std::cout<<"vertices: \n";
    std::vector<VertexId> vec= gr.getVertices();


    std::vector<VertexId>::iterator it2;
    /*
    for(it2 = vec.begin(); it2 != vec.end(); ++it2){
         std::cout<<(*it2)<<" ";
    }*/
    for(auto t:vec){
       std::cout<<t<<" ";
    }

    std::cout <<"\n";

    vec = gr.getNeighbors(v[1]);
    std::cout<<"Neighbors of v[1] - "<<v[1].getVNumber()<<": ";
    for(auto t:vec){
       std::cout<<t<<" ";
    }
    std::cout<<"\n";
    vec = gr.getNeighbors(v[7]);
    std::cout<<"Neighbors of v[7] - "<<v[7].getVNumber()<<": ";
    for(auto t:vec){
       std::cout<<t<<" ";
    }
    std::cout <<"\n";
    std::cout <<"number of vertices: "<<gr.getNoVertices()<<"\n";
    std::cout <<"number of edges: "<<gr.getNoEdges()<<"\n";

    std::vector<std::pair<std::pair<VertexId,VertexId>,double>> wedges = gr.getEdgesAndWeights();

    std::cout<<"edges: \n";
    std::vector<std::pair<std::pair<VertexId,VertexId>,double>>::iterator wit;
    for(wit = wedges.begin(); wit != wedges.end(); ++wit){
         std::cout<<(*wit).first.first<<" "<<(*wit).first.second;
         std::cout<<" with weight: "<<(*wit).second<<"\n";
    }

    /* more raw testing
    gr.addVertex(v[9]);
    std::cout<<"vertices: \n";
    vec = gr.getVertices();
    for(it2 = vec.begin(); it2 != vec.end(); ++it2){
         std::cout<<(*it2)<<" ";
    }
    std::cout <<"\n";
    */

    return 0;
}
