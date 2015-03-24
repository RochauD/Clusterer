/**
  * @file IntegerVectorEncoding.hpp
  * @brief encoder interface implementation
  */
#ifndef _BACKEND_GENETIC_IntegerVectorEncoding_HPP
#define _BACKEND_GENETIC_IntegerVectorEncoding_HPP

// Standard libraries
#include <stdint.h>
#include <vector>
#include <unordered_map>

// Own headers
#include "AbstractGraph.hpp"
#include "ClusterEncoding.hpp"

namespace backend
{
namespace genetic
{


class IntegerVectorEncoding : public ClusterEncoding
{
public:
    /**
     * @brief create a default clustering scheme from graph g
     * @param g the graph to cluster
     */
    IntegerVectorEncoding(const common::types::AbstractGraph& g);

    /**
     * @brief move a vertex to a specific cluster
     * @param vertexId the id of the vertex to be moved
     * @param clusterId the id of the destination cluster
     * @return 0 on success and -1 on failure.
     */
    int addToCluster(VertexId vertexId, ClusterId clusterId);

    /**
     * @brief get the cluster of a vertex
     * @param vertexId the vertex for which we want to get the cluster
     * @return the clusterId of the vertex
     */
    ClusterId getClusterOfVertex(VertexId vertexId);

    /**
     * @brief get the vertices in a cluster
     * @param clusterId the cluster for which we want to get the vertices
     * @return a vector containing all vertices in the cluster
     */
    std::vector<VertexId> getVerticesInCluster(ClusterId clusterId);

    /**
     * @brief get the current encoding
     * @return the current encoding of a solution
     */
    Encoding getClusterEncoding();

    /**
     * @brief standard destructor
     */
    ~IntegerVectorEncoding();

private:
    Encoding encoding;
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_IntegerVectorEncoding_HPP
