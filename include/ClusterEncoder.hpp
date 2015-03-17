/**
  * @file ClusterEncoder.hpp
  * @brief cluster encoder interface
  */
#ifndef _BACKEND_GENETIC_CLUSTERENCODER_HPP
#define _BACKEND_GENETIC_CLUSTERENCODER_HPP

// Standard libraries
#include <stdint.h>
#include <vector>

// Own headers
#include "AbstractGraph.hpp"

namespace backend {
namespace genetic {


/**
 * @class ClusterEncoder
 * @interface for objects that allow a cluster to be encoded
 */
template <class Vertex, typename VertexId, typename ClusterId>
class ClusterEncoder {
 public:
     typedef std::vector<int> Encoding;
     /**
     * @brief create a default clustering scheme from graph g
     * @param g the graph to cluster
     */ 
     ClusterEncoder(const common::types::AbstractGraph<Vertex> &g);

     /**
      * @brief standard destructor
      */
     virtual ~ClusterEncoder();
     /**
     * @brief move a vertex to a specific cluster
     * @param VertexId the id of the vertex to be moved
     * @param ClusterId the id of the destination cluster
     * @return 0 on success and -1 on failure
     */
     virtual int addToCluster (VertexId vertexId, ClusterId clusterId) = 0; 
     /**
     * @brief get the current encoding of the cluster
     * @param VertexId the vertex for which we want to get the cluster
     * @return the clusterId of the vertex 
     */
     virtual ClusterId getClusterOfVertex (VertexId vertexId) = 0; 
     /**
     * @brief get the vertices in a cluster
     * @param ClusterId the cluster for which we want to get the vertices
     * @return a vector containing all vertices in the cluster
     */
     virtual std::vector< VertexId > getVerticesInCluster (ClusterId clusterId) = 0;
     /**
     * @brief get the current encoding of the cluster
     * @return the encoding of the cluster
     */
     virtual Encoding getClusterEncoding () = 0;
};

}  // namespace genetic
}  // namespace backend

#endif  // _BACKEND_GENETIC_FITNESSANALYZER_HPP

