#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../include/GraphReader2.hpp"

namespace clusterer
{
namespace backend
{

GraphReader2::GraphReader2(Graph *g):_graph(g){
}

GraphReader2::~GraphReader2(){
}

int GraphReader2::readFile(std::string file_name){
    std::ifstream myfile(file_name.c_str(), std::ios::in);

    if(myfile.fail())
    {
        std::cerr<<"Cannot open file: "<<file_name<<std::endl;
        return EXIT_FAILURE; 
    }

    this->filename = file_name;
    std::string line;

    VertexId first,second;
    //int counter = 0;
    double third = 0;

    if(myfile.is_open()){
        while(getline(myfile,line)){
        	// skip the comment lines
        	if(line[0] != '%'){
                std::istringstream iss(line);
                iss >> first >> second >> third;
                //std::cout<<first<<" "<<second<<" "<<third<<"\n";
                Vertex v1,v2;
                v1.setVNumber(first);
                v2.setVNumber(second);
                if(VertexId_map.find(v1.getVNumber()) == VertexId_map.end())
                    VertexId_map.insert(std::pair<VertexId,Vertex>(v1.getVNumber(),v1));
                if(VertexId_map.find(v2.getVNumber()) == VertexId_map.end())
                    VertexId_map.insert(std::pair<VertexId,Vertex>(v2.getVNumber(),v2));
                _graph->addEdge(VertexId_map[v1.getVNumber()],VertexId_map[v2.getVNumber()],third);	
        	}

        }
        myfile.close();
    }
    return EXIT_SUCCESS;
}

std::string GraphReader2::getFileName(){
	return filename;
}

Vertex* GraphReader2::getVertex(VertexId vid){
	if(VertexId_map.find(vid) == VertexId_map.end())
		return NULL;
	return &VertexId_map[vid];
}

std::map<VertexId,Vertex> GraphReader2::getVertexIdMap(){
	return VertexId_map;
}

} // namespace backend
} // namespace clusterer