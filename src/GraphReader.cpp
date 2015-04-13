/**
* @file GraphReader.cpp
* @brief Implementation of GraphReader
*/

// standard headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
// external headers

// internal headers
#include "../include/GraphReader.hpp"
#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{
namespace backend
{

GraphReader::GraphReader(AbstractGraph* graph) : AbstractGraphReader(graph)
{

}

GraphReader::~GraphReader()
{
}

bool GraphReader::readFile(std::string filename)
{
    std::ifstream myfile(filename, std::ios::in);

    if (myfile.fail())
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Cannot open file: ", filename);
        return false;
    }

    std::string line;
    VertexId first;
    VertexId second;
    double third = 0.0;
    std::map<VertexId, Vertex> vertexIdMap;

    if (myfile.is_open())
    {
        while (std::getline(myfile,line))
        {
            // skip the comment lines
            if (line[0] != '%')
            {
                std::istringstream iss(line);
                iss >> first >> second >> third;
                Vertex v1(first);
                Vertex v2(second);
                if (vertexIdMap.find(v1.getVNumber()) == vertexIdMap.end())
                {
                    vertexIdMap.insert(std::pair<VertexId,Vertex>(v1.getVNumber(),v1));
                }
                if (vertexIdMap.find(v2.getVNumber()) == vertexIdMap.end())
                {
                    vertexIdMap.insert(std::pair<VertexId,Vertex>(v2.getVNumber(),v2));
                }
                this->graph->addEdge(vertexIdMap[v1.getVNumber()], vertexIdMap[v2.getVNumber()], third);
            }
        }
        myfile.close();
    }
    return true;
}

}
}
