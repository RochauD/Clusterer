/**
  * @file IntegerVectorEncoding.hpp
  * @brief encoder interface implementation
  */

#include "../include/IntegerVectorEncoding.hpp"

#include <stdint.h>
#include <vector>
#include <unordered_map>

namespace backend
{
namespace genetic
{

IntegerVectorEncoding::IntegerVectorEncoding(common::types::AbstractGraph& g) : ClusterEncoding(g)
{
    // Set encoding to be as big as the vertex array
    encoding.resize(g.getVertices().size());
}

int IntegerVectorEncoding::addToCluster(VertexId vertexId, ClusterId clusterId)
{
	if (encoding.size() < vertexId)
		return -1;
	encoding[vertexId] = clusterId;
	return 0;
}

ClusterId IntegerVectorEncoding::getClusterOfVertex(VertexId vertexId)
{
	return encoding[vertexId];
}

std::vector<VertexId> IntegerVectorEncoding::getVerticesInCluster(ClusterId clusterId)
{
	std::vector<VertexId> result; 
	//iterating through the encoding vector
	for (int i = 0; i < encoding.size(); i++)
	{
		//check if VertexId is in the cluster
		if (encoding[i] == clusterId)
			result.push_back(i);
	}
	return result;
}

ClusterEncoding::Encoding IntegerVectorEncoding::getClusterEncoding()
{
	return encoding;
}

IntegerVectorEncoding::~IntegerVectorEncoding()
{

}

}  // namespace genetic
}  // namespace backend


