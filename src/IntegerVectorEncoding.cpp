/**
  * @file IntegerVectorEncoding.hpp
  * @brief encoder interface implementation
  */

// standard headers
#include <unordered_map>
#include <map>
// external headers

// internal headers
#include "../include/IntegerVectorEncoding.hpp"

namespace clusterer
{
namespace backend
{

IntegerVectorEncoding::IntegerVectorEncoding() : ClusterEncoding()
{

}

IntegerVectorEncoding::IntegerVectorEncoding(const AbstractGraph* g) : ClusterEncoding(g)
{
    // Set encoding to be as big as the vertex array
    this->encoding.resize(g->getNoVertices());
}

int IntegerVectorEncoding::addToCluster(VertexId vertexId, ClusterId clusterId)
{
    if (this->encoding.size() < vertexId)
    {
        return -1;
    }
    this->encoding[vertexId] = clusterId;
    this->isNormalized = false;
    return 0;
}

ClusterId IntegerVectorEncoding::getClusterOfVertex(VertexId vertexId) const
{
    return this->encoding[vertexId];
}

std::vector<VertexId> IntegerVectorEncoding::getVerticesInCluster(ClusterId clusterId) const
{
    std::vector<VertexId> result;
    //iterating through the encoding vector
    for (size_t i = 0; i < this->encoding.size(); i++)
    {
        //check if VertexId is in the cluster
        if (this->encoding[i] == clusterId)
        {
            result.push_back(i);
        }
    }
    return result;
}

std::unordered_map<ClusterId, uint64_t> IntegerVectorEncoding::getClusterVerticesCountMap() const
{
    std::unordered_map<ClusterId, uint64_t> map;
    for (auto& e : this->encoding)
    {
        ++map[e];
    }
    return map;
}

uint64_t IntegerVectorEncoding::getVerticesCountInCluster(ClusterId clusterId) const
{
    std::unordered_map<ClusterId, uint64_t> map;
    for (auto& e : this->encoding)
    {
        ++map[e];
    }
    return map[clusterId];
}

uint32_t IntegerVectorEncoding::getClusterCount() const
{
    std::unordered_map<ClusterId, uint64_t> map;
    for (auto& e : this->encoding)
    {
        ++map[e];
    }
    return map.size();
}

ClusterEncoding::Encoding IntegerVectorEncoding::getEncoding()
{
    return  this->encoding;
}

unsigned IntegerVectorEncoding::size() const
{
    return this->encoding.size();
}

int IntegerVectorEncoding::normalize()
{
    // Don't run the algorithm if not necessary
    if (isNormalized)
    { return 0; }

    std::map<ClusterId, VertexId> minVertex;
    VertexId i;

    // Find the minimum vertex id in each cluster
    for (i = 0; i < this->encoding.size(); i++)
    {
        if (minVertex.find(this->encoding[i]) == minVertex.end())
        {
            // Newly found cluster
            minVertex[this->encoding[i]] = i;
        }
        else if (i < minVertex[this->encoding[i]])
        {
            // vertexId smaller than the current smallest
            minVertex[encoding[i]] = i;
        }
    }

    // Rename all clusters
    for (i = 0; i < this->encoding.size(); i++)
    {
        this->encoding[i] = minVertex[this->encoding[i]];
    }

    // Change the labels to be in [0, clusterCount)
    bool changed = true;
    int newId = 1, min, last = 0;
    int invalidClusterId = this->encoding.size() + 1;
    while (changed)
    {
        changed = false;
        min = invalidClusterId;
        for (i = 0; i < this->encoding.size(); i++)
        {
            if (this->encoding[i] > last && this->encoding[i] < min)
            {
                min = this->encoding[i];
            }
        }

        if (min != invalidClusterId)
        {
            changed = true;
            for (i = 0; i < this->encoding.size(); i++)
            {
                if (this->encoding[i] == min)
                {
                    this->encoding[i] = newId;
                }
            }
            last = min;
            newId++;
        }
    }
    // Keep internal track of normalization state
    isNormalized = true;
    return 0;
}

IntegerVectorEncoding::~IntegerVectorEncoding()
{
}

}
}
