/**
* @file Vertex.hpp
* @brief
*/
#ifndef CLUSTERER_BACKEND_VERTEX_CLASS_H
#define CLUSTERER_BACKEND_VERTEX_CLASS_H

// standard headers
#include <string>
#include <vector>
#include <cstdint>
// external headers

// internal headers

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

typedef uint64_t VertexId;
typedef uint64_t ClusterId;

/**
 * @class Vertex
 * @brief A wrapper class around a boost vertex, representing a node in our graph 
 */
class Vertex
{
    public:
        /**
         * @brief Standart constructor
         */
        Vertex();
        /**
         * @brief Constructor with a custom vertex id
         * @param The custom vertex id
         */
        Vertex(VertexId);
        /**
         * @brief Copy constructor
         * @param The vertex to copy from 
         */
        Vertex(const Vertex&);
        /**
         * @brief Standart destructor
         */
        ~Vertex();
        /**
         * @brief Gets the number of the vertex
         * @return The vertex number
         */
        VertexId getVNumber() const;
        /**
         * @brief Sets the id of the vertex
         * @param The number representing the new vertex id
         */
        void setVNumber(VertexId);
        /**
         * @brief Adds a neighbour to the vertex
         * @param The vertex to which this one is connected
         */
        void addNeighbor(const Vertex&);
        /**
         * @brief Checks if this vertex is connected to another one
         * @return Whether or not the vertices have an edge between them
         */
        bool hasNeighbor(Vertex&);
        /**
         * @brief Check if two vertices are identical
         * @brief param The vertex to compare to
         */
        bool operator==(Vertex&);
    protected:
    private:
        VertexId number;
        std::vector<Vertex> neighbors;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
