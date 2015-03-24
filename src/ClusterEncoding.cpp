/**
  * @file ClusterEncoding.cpp
  * @implementation of ClusterEncoding.hpp
  */

#include "../include/ClusterEncoding.hpp"
#include "../include/Vertex.hpp"

namespace backend
{
namespace genetic
{

ClusterEncoding::ClusterEncoding(const common::types::AbstractGraph& g) : graph(g)
{

}

ClusterEncoding::~ClusterEncoding() {}

}  // namespace genetic
}  // namespace backend