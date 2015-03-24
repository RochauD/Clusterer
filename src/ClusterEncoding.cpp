/**
  * @file ClusterEncoding.cpp
  * @implementation of ClusterEncoding.hpp
  */

#include "../include/ClusterEncoding.hpp"

namespace backend
{
namespace genetic
{

ClusterEncoding::ClusterEncoding(common::types::AbstractGraph& g) : graph(g)
{

}

ClusterEncoding::~ClusterEncoding() {}

}  // namespace genetic
}  // namespace backend