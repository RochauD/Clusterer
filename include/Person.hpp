/**
  * @brief  PersonId and Person definitions
  * @file   Person.hpp
  *
  */

#ifndef CLUSTERER_BACKEND_PERSON_HPP
#define CLUSTERER_BACKEND_PERSON_HPP

// standard headers
#include <stdint.h>
#include <cinttypes>
#include <string>
#include <vector>
#include <utility>
// external headers

// internal headers
#include "Parcelable.hpp"

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
 * @brief Person Id uniquely representing a person
 */
typedef uint64_t PersonId;
#define PRIpersonId PRIu64

/**
 * @class Person
 * @brief representation of a Social Network Person
 * @todo fix this class. Currently outcommented as it is not compiling
 */
struct Person : public Parcelable
{
    std::string sourceDoc;
    std::string name;
    std::vector<PersonId> relations;

    Person();

    Person(std::string sourceDoc, std::string name,
           std::vector<PersonId> relations)
        : sourceDoc(std::move(sourceDoc)), name(std::move(name)),
          relations(std::move(relations)) {}

    ~Person();

    inline bool operator!=(const Person& rhs) const
    {
        if (relations.size() != rhs.relations.size()) { return false; }

        for (size_t i = 0; i < relations.size(); i++)
        {
            if (relations[i] != rhs.relations[i]) { return false; }
        }
        return name != rhs.name;
    }

    virtual const size_t getParcelableSize()
    {
        ParcelAllocator parcelAllocator;
        parcelAllocator.reserve(sourceDoc);
        parcelAllocator.reserve(name);
        for (const auto& relation : relations)
        {
            parcelAllocator.reserve(std::to_string(relation));
        }
        return parcelAllocator.getSize();
    }

    virtual void writeToParcel(ParcelEncoder* encoder) const
    {
        encoder->encode(sourceDoc);
        encoder->encode(name);
        for (const auto& relation : relations)
        {
            encoder->encode(std::to_string(relation));
        }
    }

    virtual void readFromParcel(ParcelDecoder* decoder)
    {
        // This was provided by group 2 but does not compile
        // decoder->decode(&sourceDoc);
        // decoder->decode(&name);
        // decoder->decode(&relations);
    }
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
