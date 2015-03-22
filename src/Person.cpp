/**
  * @brief  PersonId and Person definitions
  * @file   Person.hpp
  */

#include <stdint.h>

#include <cinttypes>
#include <string>
#include <vector>
#include <utility>

#include "../include/Parcelable.hpp"

namespace common {
namespace types {

/**
 * @brief Person Id uniquely representing a person
 */

Person::Person()
{

}


Person::Person(std::string sourceDoc = "", std::string name,
                std::vector<PersonId> relations)
        : sourceDoc(std::move(sourceDoc)), name(std::move(name)),
        relations(std::move(relations))
{

}


}  // namespace types
}  // namespace common
