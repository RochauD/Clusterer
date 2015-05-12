/**
* @file ClusteringPopulationRefiner.hpp
* @brief In this file the class ClusteringPopulationRefiner is defined. This class is used to
* refine a population in the refinement phase.
*/
#ifndef CLUSTERER_BACKEND_CLUSTERING_POPULATION_REFINER_HPP
#define CLUSTERER_BACKEND_CLUSTERING_POPULATION_REFINER_HPP

// standard headers
#include <thread>
#include <vector>
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
* @class ClusteringPopulationRefiner
* @brief Class which refines a population during the refinement phase.
* @tparam ClusteringSolutionRefinerFunction The function used to refine a member of the population.
* The ClusteringSolutionRefinerFunction type needs to have a function with the following prototype:
* void refine(EncodingType, AbstractGraph)
* @tparam EncodingFitnessDataStructure The data structure which represents a population.
*/
template<class ClusteringSolutionRefinerFunction, class EncodingFitnessDataStructure>
class ClusteringPopulationRefiner
{
    public:
        /**
        * @brief Constructor that creates a ClusteringPopulationRefiner object from the given parameters.
        * @param graph A pointer to the underlying graph object.
        * @param populationPtr A pointer to the underlying population.
        * @param mutationProbability The mutation probability.
        * @param maxMinDensityClusterProbability The maxMinDensityClusterProbability.
        * @param threadCount The threadCount.
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

        /**
        * @var graph
        * @brief A pointer to the underlying graph object.
        */
        const AbstractGraph* graph;

        /**
        * @var populationPtr
        * @brief A pointer to the underlying population object.
        */
        EncodingFitnessDataStructure* populationPtr;

        /**
        * @var threadCount
        * @brief The number of threads used int the evaluation.s
        */
        size_t threadCount;

        /**
        * @var randomDeviceVec
        * @brief A vector of random devices used to generate random numbers.
        */
        std::vector<std::mt19937> randomDeviceVec;

        /**
        * @var mutationProbability
        * @brief The mutation probability.
        */
        double mutationProbability;

        /**
        * @var maxMinDensityClusterProbability
        * @brief The maxMinDensityClusterProbability.
        */
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
