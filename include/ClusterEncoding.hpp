/**
 * @file ClusterEncoding.hpp
 * @brief cluster encoder interface
 */
#ifndef CLUSTERER_BACKEND_CLUSTER_ENCODING_HPP
#define CLUSTERER_BACKEND_CLUSTER_ENCODING_HPP

// standard headers
#include <stdint.h>
#include <vector>
// external headers

// internal headers
#include "AbstractGraph.hpp"
#include "Vertex.hpp"

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{

/**
 * @class ClusterEncoding
 * @interface for objects that allow a cluster to be encoded
 */
class ClusterEncoding
{
    public:
        typedef std::vector<ClusterId> Encoding;
        /**
        * @brief create a default clustering scheme from graph g
        * @param g the graph to cluster
        */
        ClusterEncoding(AbstractGraph& g);

        /**
         * @brief standard destructor
         */
        virtual ~ClusterEncoding();
        /**
        * @brief move a vertex to a specific cluster
        * @param VertexId the id of the vertex to be moved
        * @param ClusterId the id of the destination cluster
        * @return 0 on success and -1 on failure
        */
        virtual int addToCluster(VertexId vertexId, ClusterId clusterId) = 0;
        /**
        * @brief get the current encoding of the cluster
        * @param VertexId the vertex for which we want to get the cluster
        * @return the clusterId of the vertex
        */
        virtual ClusterId getClusterOfVertex(VertexId vertexId) = 0;
        /**
        * @brief get the vertices in a cluster
        * @param ClusterId the cluster for which we want to get the vertices
        * @return a vector containing all vertices in the cluster
        */
        virtual std::vector< VertexId > getVerticesInCluster(ClusterId clusterId) = 0;
        /**
         * @brief get the current encoding
         * @return the current encoding of a solution
         */
        virtual Encoding getEncoding() = 0;

    protected:
        AbstractGraph& graph;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif  // _BACKEND_GENETIC_ClusterEncoding_HPP


