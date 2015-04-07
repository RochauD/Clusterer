#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../include/GraphReader.hpp"


GraphReader::GraphReader(std::string filename)
{
    this->filename = filename;
}


GraphReader::~GraphReader()
{

}

std::string GraphReader::getFilename()
{
    return filename;
}

void GraphReader::setFilename(std::string filename)
{
    this->filename = filename;
}

uint64_t GraphReader::readFile()
{

    uint64_t startNode;
    uint64_t endNode;
    uint64_t edgeWeight;
    uint64_t size = 0;
    uint64_t edgesNo = 0;

    std::vector<uint64_t> totalVertices;
    std::ifstream file(filename.c_str(), std::ios::in);

    if(file.fail())
    {
        std::cerr<<"Cannot open file!"<<std::endl;
        return EXIT_FAILURE;
    }


    while(file >> startNode >> endNode >> edgeWeight)
    {
        uint64_t check = 0;
        uint64_t check1 = 0;
        /*
        storing the vertices of first edge in the vector totalVertices. And in each iteration, the
        startNode and endNode are compared to the element of totalVertices. check variable is used
        to check the duplicacy of startNode in totalVertices. If the startNode is already in totalVertices
        the value of check won't be equal to the size of totalVertices. As a result this startNode won't
        be added to totalVertices and vice versa. Same logic is used for endNode and check1.
        */

        if (totalVertices.size() == 0)
        {
            totalVertices.push_back(startNode);
            totalVertices.push_back(endNode);
        }
        else
        {
            for(unsigned int i=0; i<totalVertices.size(); i++)
            {
                if(startNode != totalVertices[i])
                {
                    check++;
                }

                if(endNode != totalVertices[i])
                {
                    check1++;
                }

            }
            size = totalVertices.size();
            if(check == size)
            {
                totalVertices.push_back(startNode);
            }
            if(check1 == size)
            {
                totalVertices.push_back(endNode);
            }
        }

        edges.push_back(std::make_pair(startNode,endNode));
        edgesNo++;
        edgesWeight.push_back(std::make_pair(std::make_pair(startNode,endNode),edgeWeight));
        if(file.eof()) break;

    }

    vertices = totalVertices;
    verticesCount = totalVertices.size();
    edgesCount = edgesNo;
    file.close();

    return EXIT_SUCCESS;
}


std::vector<std::pair<uint64_t,uint64_t> > GraphReader::getEdges()
{
    return edges;
}

void GraphReader::printEdges(std::vector<std::pair<uint64_t,uint64_t> > graphEdges)
{
    for(unsigned int i=0; i < graphEdges.size(); i++)
    {
        std::cout<<graphEdges[i].first<<" "<<graphEdges[i].second<<std::endl;
    }

}


std::vector<std::pair<std::pair<uint64_t,uint64_t>, uint64_t > > GraphReader::getEdgesWeight()
{
    return edgesWeight;
}

void GraphReader::printEdgesWeight(std::vector<std::pair<std::pair<uint64_t,uint64_t>, uint64_t > >graphEdgesWeight)
{
    for(unsigned int i=0; i < graphEdgesWeight.size(); i++)
    {
        std::cout<<graphEdgesWeight[i].first.first<<" "<<graphEdgesWeight[i].first.second<<" "<<graphEdgesWeight[i].second<<std::endl;
    }

}

std::vector<uint64_t> GraphReader::getVertices()
{
    return vertices;
}

void GraphReader::printVertices(std::vector<uint64_t> graphVertices)
{
   for(unsigned int i=0; i < graphVertices.size(); i++)
   {
       std::cout<<graphVertices[i]<<std::endl;
   }
}

uint64_t GraphReader::getVerticesCount()
{
    return verticesCount;
}

uint64_t GraphReader::getEdgesCount()
{
    return edgesCount;
}
