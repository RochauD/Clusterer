/**
* @file Vertex.cpp
*/

#include "../include/Vertex.hpp"

namespace clusterer
{
namespace backend
{

Vertex::Vertex()
{
}

Vertex::Vertex(VertexId n)
{
    this->number = n;
}

Vertex::Vertex(const Vertex& v)
{
    number = v.number;
    for (auto it = v.neighbors.begin(); it != v.neighbors.end(); ++it)
    {
        neighbors.push_back(*it);
    }
}

Vertex::~Vertex() {}

VertexId Vertex::getVNumber() const
{
    return number;
}

void Vertex::setVNumber(VertexId x)
{
    number = x;
}

void Vertex::addNeighbor(const Vertex& v)
{
    neighbors.push_back(v);
}

bool Vertex::hasNeighbor(Vertex& v)
{
    std::vector<Vertex>::iterator it;
    for (it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        if ((*it).getVNumber() == v.getVNumber())
        {
            return true;
        }
    }
    return false;
}

bool Vertex::operator==(Vertex& v)
{
    return number == v.getVNumber(); // number of vertex should be unique
}

}
}
