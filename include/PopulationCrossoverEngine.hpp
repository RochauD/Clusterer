/**
* @file PopulationCrossoverEngine.hpp
* @brief PopulationCrossoverEngine is a class that applies a crossover function to a population
*/
#ifndef CLUSTERER_BACKEND_POPULATION_DOUBLE_CROSSOVER_ENGINE_HPP
#define CLUSTERER_BACKEND_POPULATION_DOUBLE_CROSSOVER_ENGINE_HPP

// standard headers
#include <thread>
#include <vector>
#include <random>
#include <future>
// external headers

// internal headers
#include "AbstractGraph.hpp"

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
* @class PopulationCrossoverEngine
* @brief PopulationCrossoverEngine is a class that mutates each member of a population
* with a certain probability.
*/
template<class EncodingFitnessDataStructure, class Encoding, class CrossoverFunction, class SelectorFunction>
class PopulationCrossoverEngine
{
    public:
        /**
        * @brief standard constructor
        */
        PopulationCrossoverEngine(const AbstractGraph* graph, EncodingFitnessDataStructure* populationPtr, size_t iterationCount, size_t threadCount = 1);

        /**
        * @brief standard destructor
        */
        ~PopulationCrossoverEngine();

        /**
        * @brief Mutate the given population.
        * @return void
        */
        void crossoverPopulation();
    protected:
    private:
        /**
        * @brief Evaluates the given sub population.
        * @return void
        */
        EncodingFitnessDataStructure crossoverSubPopulation(size_t iterationCount, size_t threadID);

        const AbstractGraph* graph;
        EncodingFitnessDataStructure* populationPtr;
        std::vector<std::mt19937> randomDeviceVec;
        size_t threadCount;
        size_t iterationCount;
};

template<class EncodingFitnessDataStructure, class Encoding, class CrossoverFunction, class SelectorFunction>
PopulationCrossoverEngine<EncodingFitnessDataStructure, Encoding, CrossoverFunction, SelectorFunction>::
PopulationCrossoverEngine(const AbstractGraph* graph, EncodingFitnessDataStructure* populationPtr, size_t iterationCount, size_t threadCount)
{
    this->graph = graph;
    this->populationPtr = populationPtr;
    this->threadCount = threadCount;
    this->iterationCount = iterationCount;
    std::random_device rd;
    this->randomDeviceVec = std::vector<std::mt19937>(threadCount, std::mt19937(rd()));
}

template<class EncodingFitnessDataStructure, class Encoding, class CrossoverFunction, class SelectorFunction>
PopulationCrossoverEngine<EncodingFitnessDataStructure, Encoding, CrossoverFunction, SelectorFunction>::
~PopulationCrossoverEngine()
{

}

template<class EncodingFitnessDataStructure, class Encoding, class CrossoverFunction, class SelectorFunction>
void PopulationCrossoverEngine<EncodingFitnessDataStructure, Encoding, CrossoverFunction, SelectorFunction>::
crossoverPopulation()
{
    std::vector<std::future<EncodingFitnessDataStructure>> futurePool;
    futurePool.reserve(this->threadCount);

    // compute slice size
    size_t normalIterationSliceSize = this->iterationCount / this->threadCount;
    size_t additionalIterations = this->iterationCount % this->threadCount;
    size_t currentIterationCount = 0;

    // start tasks
    for (size_t i = 0; i < this->threadCount; ++i)
    {
        currentIterationCount = normalIterationSliceSize;
        if (additionalIterations > 0)
        {
            ++currentIterationCount;
            --additionalIterations;
        }
        futurePool.push_back(std::async(std::launch::async,
                                        &PopulationCrossoverEngine<EncodingFitnessDataStructure, Encoding, CrossoverFunction, SelectorFunction>::crossoverSubPopulation,
                                        this,
                                        currentIterationCount,
                                        i));
    }

    // get and combine result and insert it into the population
    EncodingFitnessDataStructure result;
    result.reserve(this->iterationCount * 2);
    EncodingFitnessDataStructure subResult;
    for (auto& future : futurePool)
    {
        subResult = future.get();
        result.insert(result.end(), subResult.begin(), subResult.end());
    }
    this->populationPtr->insert(this->populationPtr->end(), result.begin(), result.end());

}

template<class EncodingFitnessDataStructure, class Encoding, class CrossoverFunction, class SelectorFunction>
EncodingFitnessDataStructure PopulationCrossoverEngine<EncodingFitnessDataStructure, Encoding, CrossoverFunction, SelectorFunction>::
crossoverSubPopulation(size_t iterationCount, size_t threadID)
{
    CrossoverFunction crossover(&(this->randomDeviceVec[threadID]));
    SelectorFunction selector(this->populationPtr,&(this->randomDeviceVec[threadID]));
    EncodingFitnessDataStructure result;
    result.reserve(iterationCount * 2);
    Encoding firstChild(this->graph);
    Encoding secondChild(this->graph);

    for (size_t i = 0; i < iterationCount; i++)
    {
        auto indices = selector.selectTwoClusters();
        crossover.crossover((*this->populationPtr)[indices.first].populationEncoding, (*this->populationPtr)[indices.second].populationEncoding, firstChild, secondChild);
        PopulationMember<Encoding, double> member1;
        member1.fitnessValue = 0.0;
        member1.modified = true;
        member1.populationEncoding = firstChild;
        PopulationMember<Encoding, double> member2;
        member2.fitnessValue = 0.0;
        member2.modified = true;
        member2.populationEncoding = secondChild;

        result.push_back(member1);
        result.push_back(member2);
    }

    return result;
}

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
