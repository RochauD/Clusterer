/**
 * @file Selector.hpp
 * @brief Selector for picking individuals for a crossover
 */
#ifndef CLUSTERER_BACKEND_SELECTOR_HPP
#define CLUSTERER_BACKEND_SELECTOR_HPP

// standard headers
#include <utility>
#include <vector>
#include <cstdint>
#include <random>

// external headers

// internal headers
#include "AbstractGraph.hpp"
#include "ClusterEncoding.hpp"

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
 * @class Selector
 * @brief Class to pick two individuals for a crossover
 */
template<class EncodingFitnessDataStructure>
class Selector
{
    public:

        /**
         * @brief Constructor for the selector
         * @param population The population from which we are picking
         */
        Selector(EncodingFitnessDataStructure* population, std::mt19937* gen);

        /**
         * @brief Selects two individuals from the given population
         * @return A pair of indices pointing to the selected elements
         */
        std::pair<size_t, size_t> selectTwoIndividuals();

        /**
         * @brief Select n individuals from the given population
         * @param howMany The number of individuals to select
         * @param unique Whether or not we require the individuals to be unique
         * @return A vector of indices pointing to the selected individuals
         */
        std::vector<size_t> selectIndividuals(size_t howMany, bool unique = false);

        /**
         * @brief standard destructor
         */
        ~Selector();

    private:
        EncodingFitnessDataStructure* population;
        std::mt19937* rng;
        std::uniform_real_distribution<double> uni_dist = std::uniform_real_distribution<double>(0.0, 1.0);

        /**
         * @brief Fills out probSum with the probabilities of picking each member
         * of the population except the one with index without
         * @param probSum The vector of probabilities to fill
         * @param without The index of the individual to skip
         */
        void generateRollingSum(std::vector<double>& probSum, std::vector<size_t> without = std::vector<size_t>());

        /**
         * @brief Picks a random if based on the probabilities in probSum
         * @param probSum A rolling sum of the probabilities to pick each element
         * @param without The element that was skipped and is not included in probSum
         */
        size_t getRandomId(const std::vector<double>& probSum, std::vector<size_t> without = std::vector<size_t>());
};

template<class EncodingFitnessDataStructure>
Selector<EncodingFitnessDataStructure>::Selector(EncodingFitnessDataStructure* ppl, std::mt19937* gen) : population(ppl)
{
    rng = gen;
}

template<class EncodingFitnessDataStructure>
Selector<EncodingFitnessDataStructure>::~Selector()
{
}

template<class EncodingFitnessDataStructure>
std::pair<size_t, size_t> Selector<EncodingFitnessDataStructure>::selectTwoIndividuals()
{
    std::vector<size_t> ind = this->selectIndividuals(2, true);
    return std::make_pair(ind[0], ind[1]);
}

template<class EncodingFitnessDataStructure>
std::vector<size_t> Selector<EncodingFitnessDataStructure>::selectIndividuals(size_t howMany, bool unique)
{
    std::vector<size_t> picked;
    std::vector<double> probabilities;

    generateRollingSum(probabilities);

    for (size_t i = 0; i < howMany; i++)
    {
        if (unique)
        {
            // Exclude the already picked ones and re-calculate the probabilities
            picked.push_back(this->getRandomId(probabilities, picked));
            generateRollingSum(probabilities, picked);
        }
        else
        {
            // Just pick one
            picked.push_back(this->getRandomId(probabilities));
        }
    }

    return picked;   
}

template<class EncodingFitnessDataStructure>
void Selector<EncodingFitnessDataStructure>::generateRollingSum(std::vector<double>& probSum, std::vector<size_t> without)
{
    size_t size = population->size() - without.size();
    if (size > probSum.size())
    {
        // Allocate memory if necessary
        probSum.resize(size);
    }

    double sum = 0.0;

    // Get the total sum everywhere
    size_t ind = 0;
    for (size_t i = 0; i < population->size(); i++)
    {
        // skip this index if we have to
        if (find(without.begin(), without.end(), i) != without.end())
        {
            continue;
        }

        sum += (*population)[i].second;
        probSum[ind] = sum;
        ind++;
    }

    // Now devide everything by sum so that we get numbers in [0, 1]
    for (size_t i = 0; i < size; i++)
    {
        probSum[i] = probSum[i] / sum;
    }
}

template<class EncodingFitnessDataStructure>
size_t Selector<EncodingFitnessDataStructure>::getRandomId(const std::vector<double>& probSum, std::vector<size_t> without)
{
    // Random double in [0, 1]
    double rnum = uni_dist((*rng));

    // 1st (edge) case, necessary for the binary search to work properly
    if (rnum < probSum[0])
    {
        int ind = 0;
        while (find(without.begin(), without.end(), ind) != without.end())
        {
            ind++;
        }
        return ind;
    }

    // Use binary search to find in which interval does the random number fall
    size_t l = 0;
    size_t r = probSum.size();
    while (l + 1 < r)
    {
        int m = (l + r) / 2;
        if (probSum[m] > rnum)
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    while (find(without.begin(), without.end(), r) != without.end())
    {
        r++;
    }

    return r;
}


}   // End namespaces
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
