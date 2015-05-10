/**
* @file PopulationMember.hpp
* @brief File in which the PopulationMember structure is defined.
*/
#ifndef CLUSTERER_BACKEND_POPULATION_MEMBER_HPP
#define CLUSTERER_BACKEND_POPULATION_MEMBER_HPP

// standard headers

// external headers

// internal headers


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
* @struct PopulationMember
* @brief A member of a clustering population.
* @tparam Encoding The Encoding used.
*/
template<class Encoding, class FitnessType>
struct PopulationMember
{
    /**
    * @var populationEncoding
    * @brief The encoding of a clusterer solution.
    */
    Encoding populationEncoding;

    /**
    * @var fitnessValue
    * @brief The fitness value of the encoding.
    */
    FitnessType fitnessValue;

    /**
    * @var modified
    * @brief A boolean flag that determines whether or not a modification took place during an iteration.
    */
    bool modified;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
