/**
 * @file PersonDb.hpp
 * @brief Person database interface
 */
#ifndef CLUSTERER_BACKEND_PERSONDB_HPP
#define CLUSTERER_BACKEND_PERSONDB_HPP

// standard headers
#include <stdint.h>
#include <functional>
// external headers

// internal headers
#include "Person.hpp"

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

typedef std::function<int (const Person&)> QueryCallback;

/**
 * @class PersonDb
 * @brief interface for databases which allow person insertion
 */
class PersonDb
{
    public:
        virtual ~PersonDb() {}

        /**
         * @brief insert person in database
         * @param person to be inserted in the database
         * @return 0 on success and -1 on failure.
         */
        virtual int insertPerson(const Person& person) = 0;

        /**
         * @brief query person in database
         * @param personId id of a person in the database
         * @param limitMin start position to look for person
         * @param limitSize maximum number of person returned
         * @param queryCallback the function to be called when a person is
         * discovered
         * @return 0 on success and -1 on failure.
         */
        virtual int queryPerson(const PersonId& personId,
                                uint64_t limitMin,
                                uint64_t limitSize,
                                QueryCallback queryCallback) = 0;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
