/**
 * @file IntegerVectorEncoding.hpp
 * @brief encoder interface implementation
 */
#ifndef CLUSTERER_BACKEND_INTEGER_VECTOR_ENCODING_HPP
#define CLUSTERER_BACKEND_INTEGER_VECTOR_ENCODING_HPP

// standard headers
#include <stdint.h>
#include <vector>
#include <unordered_map>
// external headers

// internal headers
#include "Graph.hpp"
#include "ClusterEncoding.hpp"

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

class IntegerVectorEncoding : public ClusterEncoding
{
    public:
        /**
         * @brief create a default clustering scheme from graph g
         * @param g the graph to cluster
         */
        IntegerVectorEncoding(const Graph* g);
         
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
        ClusterId getClusterOfVertex(VertexId vertexId) const;

        /**
         * @brief get the vertices in a cluster
         * @param clusterId the cluster for which we want to get the vertices
         * @return a vector containing all vertices in the cluster
         */
        std::vector<VertexId> getVerticesInCluster(ClusterId clusterId) const;

        /**
        * @brief Returns a map that maps ClusterIds to the corresponding vertices count.
        * @return The hashmap.
        * @todo add a test for this function
        */
        std::unordered_map<ClusterId, uint64_t> getClusterVerticesCountMap() const;

        /**
        * @brief Returns the number of vertices in a cluster.
        * @return The number of vertices in a cluster of the solution.
        * @todo add a test for this function
        */
        uint64_t getVerticesCountInCluster(ClusterId clusterId) const;

        /**
        * @brief Returns the number of clusters in the solution.
        * @return The number of clusters in the solution.
        * @todo add a test for this function
        */
        uint32_t getClusterCount() const;

        /**
         * @brief get the current encoding
         * @return the current encoding of a solution
         */
        ClusterEncoding::Encoding getEncoding();
        
        /**
         * @brief get the size of the current encoding
         * @return the number of vertices
         */
        uint32_t size() const;

        /**
         * @brief does a renumbering procedure to ensure unique representation of a solution
         * @return 0 on success -1 on failiure
         */
        int32_t normalize();

        /**
         * @brief standard destructor
         */
        ~IntegerVectorEncoding();

    private:
        bool isNormalized = false;
        ClusterEncoding::Encoding encoding;
        const Graph* graph;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
