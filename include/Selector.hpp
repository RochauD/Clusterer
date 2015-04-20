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
         * @brief Selects two clusters from the given population
         * @return A pair of indices pointing to the selected elements
         */
        std::pair<uint64_t, uint64_t> selectTwoClusters();

        /**
         * @brief standard destructor
         */
        ~Selector();

    private:
        EncodingFitnessDataStructure* population;
        std::mt19937* rng;
        std::uniform_real_distribution<double> uni_dist = std::uniform_real_distribution<double>(0.0, 1.0);

        /**
         * @brief A constant to denote no individual is skipped
         */
        static const uint64_t NOTHING = std::numeric_limits<uint64_t>::max();

        /**
         * @brief Fills out probSum with the probabilities of picking each member
         * of the population except the one with index without
         * @param probSum The vector of probabilities to fill
         * @param without The index of the individual to skip
         */
        void generateRollingSum(std::vector<double>& probSum, uint64_t without = NOTHING);

        /**
         * @brief Picks a random if based on the probabilities in probSum
         * @param probSum A rolling sum of the probabilities to pick each element
         * @param without The element that was skipped and is not included in probSum
         */
        uint64_t getRandomId(const std::vector<double>& probSum, uint64_t without = NOTHING);
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
std::pair<uint64_t, uint64_t> Selector<EncodingFitnessDataStructure>::selectTwoClusters()
{
    std::pair<uint64_t, uint64_t> result;
    std::vector<double> probabilities;

    // Pick the first parent
    generateRollingSum(probabilities);
    result.first = getRandomId(probabilities);
    // Now do this again without the number we first picked
    generateRollingSum(probabilities, result.first);
    result.second = getRandomId(probabilities, result.first);

    return result;
}


template<class EncodingFitnessDataStructure>
void Selector<EncodingFitnessDataStructure>::generateRollingSum(std::vector<double>& probSum, uint64_t without)
{
    uint64_t size = population->size();
    if (without != -1)
    {
        size--;
    }
    probSum.resize(size);
    double sum = 0.0;

    // Get the total sum everywhere
    uint64_t ind = 0;
    for (uint64_t i = 0; i < population->size(); i++)
    {
        // skip this index
        if (i == without)
            { continue; }

        sum += (*population)[i].second;
        probSum[ind] = sum;
        ind++;
    }
    
    // Now devide everything by sum so that we get numbers in [0, 1]
    for (uint64_t i = 0; i < size; i++)
    {
        probSum[i] = probSum[i] / sum;
    }
}

template<class EncodingFitnessDataStructure>
uint64_t Selector<EncodingFitnessDataStructure>::getRandomId(const std::vector<double>& probSum, uint64_t without)
{
    // Random double in [0, 1]
    double rnum = uni_dist((*rng));
    
    // 1st (edge) case, necessary for the binary search to work properly
    if (rnum < probSum[0]) {
        if (without == 0)
            { return 1; }
        return 0;
    }

    // Use binary search to find in which interval does the random number fall
    int l = 0;
    int r = probSum.size();
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

    if (without != NOTHING && r >= without)
    {
        // If we picked an id past the skipped one, then the actual index of the element
        // is one plus the one in the probability sum array
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
