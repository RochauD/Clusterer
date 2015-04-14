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
    this->v_info.name = "";
    this->v_info.value = -1;
    this->v_info.social_net = "";
}

Vertex::Vertex(const Vertex& v)
{
    number = v.number;
    v_info.name = v.v_info.name;
    v_info.value = v.v_info.value;
    v_info.social_net = v.v_info.social_net;
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

info Vertex::getVInfo()
{
    return v_info;
}

void Vertex::setVInfo(const info& inf)
{
    v_info.name = inf.name;
    v_info.value = inf.value;
    v_info.social_net = inf.social_net;
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
