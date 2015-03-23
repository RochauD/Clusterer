/**
  * @file IntegerVectorEncoder.hpp
  * @brief encoder interface implementation
  */

#include "../include/IntegerVectorEncoder.hpp"

#include <stdint.h>
#include <vector>
#include <unordered_map>

namespace backend
{
namespace genetic
{

IntegerVectorEncoder::IntegerVectorEncoder(const common::types::AbstractGraph& g) : ClusterEncoder(g)
{

}


}  // namespace genetic
}  // namespace backend


