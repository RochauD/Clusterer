
#include "../include/Vertex.hpp"

Vertex::Vertex()
{
}

Vertex::Vertex(int n)
{
    if (n < 0)
    {
        numberFlag = false;
        number = -1;
    }
    else number = n;

    v_info.name = "unspecified";
    v_info.value = -1;
    v_info.social_net = "unspecified";
}

Vertex::Vertex(const Vertex& v)
{
    number = v.number;
    v_info.name = v.v_info.name;
    v_info.value = v.v_info.value;
    v_info.social_net = v.v_info.social_net;
    for (std::vector<Vertex>::const_iterator it = v.neighbors.begin();
            it != v.neighbors.end(); ++it)
    {
        neighbors.push_back(*it);
    }
}

Vertex::~Vertex() {}

int Vertex::getVNumber() const
{
    return number;
}

void Vertex::setVNumber(int x)
{
    number = x;
}

bool Vertex::getVNumberFlag()
{
    return numberFlag;
}

info Vertex::getVInfo()
{
    return v_info;
}

void Vertex::setVInfo(const info& inf)
{
    if (numberFlag == true)
    {
        v_info.name = inf.name;
        v_info.value = inf.value;
        v_info.social_net = inf.social_net;
    }
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
        if ((*it).getVNumber() == v.getVNumber()) return true;
    }
    return false;
}

bool Vertex::operator==(Vertex& v)
{
    return number == v.getVNumber(); // number of vertex should be unique
}

