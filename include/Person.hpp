/**
  * @brief  PersonId and Person definitions
  * @file   Person.hpp
  *
  */

#ifndef _COMMON_TYPES_PERSON_HPP
#define _COMMON_TYPES_PERSON_HPP

//Standard libraries
#include <stdint.h>
#include <cinttypes>
#include <string>
#include <vector>
#include <utility>

//Own libraries
#include "Parcelable.hpp"

namespace common
{
namespace types
{

/**
 * @brief Person Id uniquely representing a person
 */
typedef uint64_t PersonId;
#define PRIpersonId PRIu64

/**
 * @class Person
 * @brief representation of a Social Network Person
 */
struct Person : public common::types::Parcelable
{
    std::string sourceDoc;
    std::string name;
    std::vector<PersonId> relations;

    Person();

    Person(std::string sourceDoc, std::string name,
           std::vector<PersonId> relations)
        : sourceDoc(std::move(sourceDoc)), name(std::move(name)),
          relations(std::move(relations)) {}

    inline bool operator!=(const Person& rhs) const
    {
        if (relations.size() != rhs.relations.size()) return false;

        for (size_t i = 0; i < relations.size(); i++)
        {
            if (relations[i] != rhs.relations[i]) return false;
        }
        return name != rhs.name;
    }

    virtual const size_t getParcelableSize()
    {
        common::types::ParcelAllocator parcelAllocator;
        parcelAllocator.reserve(sourceDoc);
        parcelAllocator.reserve(name);
        for (const auto& relation : relations)
        {
            parcelAllocator.reserve(std::to_string(relation));
        }
        return parcelAllocator.getSize();
    }

    virtual void writeToParcel(common::types::ParcelEncoder* encoder) const
    {
        encoder->encode(sourceDoc);
        encoder->encode(name);
        for (const auto& relation : relations)
        {
            encoder->encode(std::to_string(relation));
        }
    }

    virtual void readFromParcel(common::types::ParcelDecoder* decoder)
    {
        // This was provided by group 2 but does not compile
        // decoder->decode(&sourceDoc);
        // decoder->decode(&name);
        // decoder->decode(&relations);
    }
};

}  // namespace types
}  // namespace common

#endif  // _COMMON_TYPES_PERSON_HPP

