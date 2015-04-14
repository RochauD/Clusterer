/**
 * @file ClusterEncoding.cpp
 * @implementation of ClusterEncoding.hpp
 */

#include "../include/ClusterEncoding.hpp"

namespace clusterer
{
namespace backend
{

ClusterEncoding::ClusterEncoding(const AbstractGraph* g)
{
    this->graph = g;
}

ClusterEncoding::~ClusterEncoding()
{

}

}
}
