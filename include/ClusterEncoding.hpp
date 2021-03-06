/**
* @file ClusterEncoding.hpp
* @brief cluster encoder interface
*/
#ifndef CLUSTERER_BACKEND_CLUSTER_ENCODING_HPP
#define CLUSTERER_BACKEND_CLUSTER_ENCODING_HPP

// standard headers
#include <stdint.h>
#include <vector>
#include <unordered_map>
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
* @brief An interface for encodings.
*/
class ClusterEncoding
{
    public:
        typedef std::vector<ClusterId> Encoding;

        /**
        * @brief default constructor
        */
        ClusterEncoding();

        /**
        * @brief create a default clustering scheme from graph g
        * @param g the graph to cluster
        */
        ClusterEncoding(const AbstractGraph* g);

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
        virtual ClusterId getClusterOfVertex(VertexId vertexId) const = 0;

        /**
        * @brief get the vertices in a cluster
        * @param ClusterId the cluster for which we want to get the vertices
        * @return a vector containing all vertices in the cluster
        */
        virtual std::vector<VertexId> getVerticesInCluster(ClusterId clusterId) const = 0;

        /**
        * @brief Returns a map that maps ClusterIds to the corresponding vertices count.
        * @return The hashmap.
        */
        virtual std::unordered_map<ClusterId, uint64_t> getClusterVerticesCountMap() const = 0;

        /**
        * @brief Returns the number of vertices in a cluster.
        * @return The number of vertices in a cluster of the solution.
        */
        virtual uint64_t getVerticesCountInCluster(ClusterId clusterId) const = 0;

        /**
        * @brief Returns the number of clusters in the solution.
        * @return The number of clusters in the solution.
        */
        virtual uint32_t getClusterCount() const = 0;

        /**
        * @brief get the current encoding
        * @return the current encoding of a solution
        */
        virtual Encoding getEncoding() const = 0;

        /**
        * @brief set the current encoding
        * @param encoding The current encoding of a solution
        * @return void
        */
        virtual void setEncoding(const Encoding& encoding) = 0;

        /**
        * @brief get the size of the current encoding
        * @return the number of vertices
        */
        virtual uint32_t size() const = 0;

        /*
        * @brief Normalizes the clustering solution
        * @return 0 on success -1 on failiure
        */
        virtual int32_t normalize();

    protected:
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
