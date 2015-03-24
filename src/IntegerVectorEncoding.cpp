/**
  * @file IntegerVectorEncoding.hpp
  * @brief encoder interface implementation
  */

#include "../include/IntegerVectorEncoding.hpp"

#include <stdint.h>
#include <vector>
#include <unordered_map>

namespace backend
{
namespace genetic
{

IntegerVectorEncoding::IntegerVectorEncoding(const common::types::AbstractGraph& g) : ClusterEncoding(g)
{
    // Set encoding to be as big as the vertex array
    encoding.resize(g.getVertices().size());
}


}  // namespace genetic
}  // namespace backend


