/**
  * @file IntegerVectorEncoding.hpp
  * @brief encoder interface implementation
  */

#include "../include/IntegerVectorEncoding.hpp"

#include <stdint.h>
#include <vector>
#include <map>

namespace backend
{
namespace genetic
{

IntegerVectorEncoding::IntegerVectorEncoding(const common::types::AbstractGraph& g) : ClusterEncoding(g)
{
    // Set encoding to be as big as the vertex array
    encoding.resize(g.getVertices().size());
}

int IntegerVectorEncoding::normalize()
{
    std::map<ClusterId, VertexId> minVertex;
    VertexId i;

    // Find the minimum vertex id in each cluster
    for (i = 0; i < encoding.size(); i++) {
        if (minVertex.find(encoding[i]) == minVertex.end()) {
            // Newly found cluster
            minVertex[encoding[i]] = i;
        } else if (i < minVertex[encoding[i]]) {
            // vertexId smaller than the current smallest
            minVertex[encoding[i]] = i;
        }
    }

    // Rename all clusters
    for (i = 0; i < encoding.size(); i++) {
        encoding[i] = minVertex[encoding[i]];
    }

    return 0;
}

}  // namespace genetic
}  // namespace backend


