/**
  * @file PersonDb.hpp
  * @brief Person database interface
  */
#ifndef _BACKEND_DBC_PERSONDB_HPP
#define _BACKEND_DBC_PERSONDB_HPP

#include <stdint.h>
#include <functional>

#include "Person.hpp"

namespace backend {
namespace dbc {

typedef std::function<int (const common::types::Person&)> QueryCallback;

/**
 * @class PersonDb
 * @brief interface for databases which allow person insertion
 */
class PersonDb {
public:
    virtual ~PersonDb() {}

    /**
     * @brief insert person in database
     * @param person to be inserted in the database
     * @return 0 on success and -1 on failure.
     */
    virtual int insertPerson(const common::types::Person& person) = 0;

    /**
     * @brief query person in database
     * @param personId id of a person in the database
     * @param limitMin start position to look for person
     * @param limitSize maximum number of person returned
     * @param queryCallback the function to be called when a person is
     * discovered
     * @return 0 on success and -1 on failure.
     */
    virtual int queryPerson(const common::types::PersonId& personId,
                            uint64_t limitMin,
                            uint64_t limitSize,
                            QueryCallback queryCallback) = 0;
};

}  // namespace dbc
}  // namespace backend

#endif  // _BACKEND_DBC_PERSONDB_HPP

