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

}


}  // namespace genetic
}  // namespace backend


