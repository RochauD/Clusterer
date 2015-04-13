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

/**
* @struct info
*/
typedef struct info
{
    std::string name;
    int value;
    std::string social_net;
} info;

typedef uint64_t VertexId;
typedef uint64_t ClusterId;

/**
* @class Vertex
*/
class Vertex
{
    public:
        Vertex();
        Vertex(VertexId);
        Vertex(const Vertex&);
        ~Vertex();
        VertexId getVNumber() const;
        info getVInfo();
        void setVNumber(VertexId);
        void setVInfo(const info&);
        void addNeighbor(const Vertex&);
        bool hasNeighbor(Vertex&);
        bool operator==(Vertex&);
    protected:
    private:
        VertexId number;
        info v_info;
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
