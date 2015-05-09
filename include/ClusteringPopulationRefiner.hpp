/**
* @file ClusteringPopulationRefiner.hpp
* @brief population refiner refines a population
*/
#ifndef CLUSTERER_BACKEND_CLUSTERING_POPULATION_REFINER_HPP
#define CLUSTERER_BACKEND_CLUSTERING_POPULATION_REFINER_HPP

// standard headers
#include <thread>
#include <vector>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
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
* @class ClusteringPopulationRefiner
* @brief object which refines a population
*/
template<class ClusteringSolutionRefinerFunction, class EncodingFitnessDataStructure>
class ClusteringPopulationRefiner
{
    public:
        /**
        * @brief standard constructor
        */
        ClusteringPopulationRefiner(const AbstractGraph* graph,
                                    EncodingFitnessDataStructure* populationPtr,
                                    double mutationProbability,
                                    double maxMinDensityClusterProbability,
                                    const size_t threadCount = 1);

        /**
        * @brief standard destructor
        */
        ~ClusteringPopulationRefiner();

        /**
        * @brief Evaluates the given population.
        * @return void
        */
        void refinePopulation();
    protected:
    private:
        /**
        * @brief Evaluates the given sub population.
        * @return void
        */
        void refineSubPopulation(size_t populationIndexBegin, size_t populationIndexEnd, size_t threadID);

        const AbstractGraph* graph;
        EncodingFitnessDataStructure* populationPtr;
        size_t threadCount;
        std::vector<std::mt19937> randomDeviceVec;
        double mutationProbability;
        double maxMinDensityClusterProbability;
};

template<class ClusteringSolutionRefinerFunction, class EncodingFitnessDataStructure>
ClusteringPopulationRefiner<ClusteringSolutionRefinerFunction, EncodingFitnessDataStructure>::ClusteringPopulationRefiner(
    const AbstractGraph* graph,
    EncodingFitnessDataStructure* populationPtr,
    double mutationProbability,
    double maxMinDensityClusterProbability,
    const size_t threadCount)
{
    this->graph = graph;
    this->mutationProbability = mutationProbability;
    this->maxMinDensityClusterProbability = maxMinDensityClusterProbability;
    this->populationPtr = populationPtr;
    this->threadCount = threadCount;
    std::random_device rd;
    this->randomDeviceVec = std::vector<std::mt19937>(threadCount, std::mt19937(rd()));
}

template<class ClusteringSolutionRefinerFunction, class EncodingFitnessDataStructure>
ClusteringPopulationRefiner<ClusteringSolutionRefinerFunction, EncodingFitnessDataStructure>::~ClusteringPopulationRefiner()
{

}

template<class ClusteringSolutionRefinerFunction, class EncodingFitnessDataStructure>
void ClusteringPopulationRefiner<ClusteringSolutionRefinerFunction, EncodingFitnessDataStructure>::refinePopulation()
{
    std::vector<std::future<void>> futurePool;
    futurePool.reserve(this->threadCount);

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
        futurePool.push_back(std::async(std::launch::async,
                                        &ClusteringPopulationRefiner<ClusteringSolutionRefinerFunction, EncodingFitnessDataStructure>::refineSubPopulation,
                                        this,
                                        populationIndexBegin,
                                        populationIndexEnd,
                                        i));
        populationIndexBegin = populationIndexEnd;
    }

    // get and combine result
    for (auto& future : futurePool)
    {
        future.get();
    }
}

template<class ClusteringSolutionRefinerFunction, class EncodingFitnessDataStructure>
void ClusteringPopulationRefiner<ClusteringSolutionRefinerFunction, EncodingFitnessDataStructure>::refineSubPopulation(
    size_t populationIndexBegin,
    size_t populationIndexEnd,
    size_t threadID)
{
    ClusteringSolutionRefinerFunction refiner(&(this->randomDeviceVec[threadID]), this->maxMinDensityClusterProbability);
    std::uniform_real_distribution<> dis(0, 1);
    for (size_t i = populationIndexBegin; i < populationIndexEnd; i++)
    {
        if (dis(this->randomDeviceVec[threadID]) < this->mutationProbability)
        {
            refiner.refine(((*this->populationPtr)[i].populationEncoding), *this->graph);
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
