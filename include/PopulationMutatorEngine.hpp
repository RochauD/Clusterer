/**
* @file PopulationMutatorEngine.hpp
* @brief PopulationMutatorEngine is a class that mutates each member of a population
* with a certain probability.
*/
#ifndef CLUSTERER_BACKEND_POPULATION_MUTATOR_ENGINE_HPP
#define CLUSTERER_BACKEND_POPULATION_MUTATOR_ENGINE_HPP

// standard headers
#include <thread>
#include <vector>
#include <random>
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
* @class PopulationMutatorEngine
* @brief PopulationMutatorEngine is a class that mutates each member of a population
* with a certain probability.
*/
template<class EncodingFitnessDataStructure, class MutatorFunction>
class PopulationMutatorEngine
{
    public:
        /**
        * @brief standard constructor
        */
        PopulationMutatorEngine(const AbstractGraph* graph, EncodingFitnessDataStructure* populationPtr, double mutationProbability = 0.05, const size_t threadCount = 1);

        /**
        * @brief standard destructor
        */
        ~PopulationMutatorEngine();

        /**
        * @brief Mutate the given population.
        * @return void
        */
        void mutatePopulation();
    protected:
    private:
        /**
        * @brief Mutates the given sub population.
        * @return void
        */
        void mutateSubPopulation(size_t populationIndexBegin, size_t populationIndexEnd, size_t threadID);

        const AbstractGraph* graph;
        EncodingFitnessDataStructure* populationPtr;
        std::vector<std::mt19937> randomDeviceVec;
        double mutationProbability;
        size_t threadCount;
};

template<class EncodingFitnessDataStructure, class MutatorFunction>
PopulationMutatorEngine<EncodingFitnessDataStructure, MutatorFunction>::PopulationMutatorEngine(const AbstractGraph* graph, EncodingFitnessDataStructure* populationPtr, double mutationProbability, const size_t threadCount)
{
    this->graph = graph;
    this->mutationProbability = mutationProbability;
    this->populationPtr = populationPtr;
    this->threadCount = threadCount;
    std::random_device rd;
    this->randomDeviceVec = std::vector<std::mt19937>(threadCount, std::mt19937(rd()));
}

template<class EncodingFitnessDataStructure, class MutatorFunction>
PopulationMutatorEngine<EncodingFitnessDataStructure, MutatorFunction>::~PopulationMutatorEngine()
{

}

template<class EncodingFitnessDataStructure, class MutatorFunction>
void PopulationMutatorEngine<EncodingFitnessDataStructure, MutatorFunction>::mutatePopulation()
{
    std::vector<std::thread> threadPool;
    threadPool.reserve(this->threadCount);

    // compute slice size
    size_t populationCount = this->populationPtr->size();
    size_t normalSliceSize = populationCount / this->threadCount;
    size_t additionalElements = populationCount % this->threadCount;
    size_t populationIndexBegin = 0;
    size_t populationIndexEnd;

    // start tasks
    for (size_t i = 0; i < this->threadCount; ++i)
    {
        populationIndexEnd = populationIndexBegin + normalSliceSize;
        if (additionalElements > 0)
        {
            ++populationIndexEnd;
            --additionalElements;
        }
        threadPool.push_back(std::thread(&PopulationMutatorEngine<EncodingFitnessDataStructure, MutatorFunction>::mutateSubPopulation, this, populationIndexBegin, populationIndexEnd, i));
        populationIndexBegin = populationIndexEnd;
    }

    // get and combine result
    for (auto& thread : threadPool)
    {
        thread.join();
    }
}

template<class EncodingFitnessDataStructure, class MutatorFunction>
void PopulationMutatorEngine<EncodingFitnessDataStructure, MutatorFunction>::mutateSubPopulation(size_t populationIndexBegin, size_t populationIndexEnd, size_t threadID)
{
    MutatorFunction mutator(&(this->randomDeviceVec[threadID]));
    std::uniform_real_distribution<> dis(0, 1);
    for (size_t i = populationIndexBegin; i < populationIndexEnd; i++)
    {
        if (dis(this->randomDeviceVec[threadID]) < this->mutationProbability)
        {
            mutator.mutate((*this->populationPtr)[i].populationEncoding);
            (*this->populationPtr)[i].modified = true;
        }
    }
}

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
