/**
* @file ClusteringPopulationSelector.hpp
* @brief In this file the class ClusteringPopulationSelector is defined. This class is used to
* select members from a population so that the reuslting population is unique.
*/
#ifndef CLUSTERER_BACKEND_CLUSTERING_POPULATION_SELECTOR_HPP
#define CLUSTERER_BACKEND_CLUSTERING_POPULATION_SELECTOR_HPP

// standard headers
#include <thread>
#include <vector>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "IntegerEncodingInitializer.hpp"
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
* @class ClusteringPopulationSelector
* @brief This class is used to select members from a population so that the reuslting population is unique.
* @tparam EncodingFitnessDataStructure The data structure which represents a population.
*/
template<class EncodingFitnessDataStructure>
class ClusteringPopulationSelector
{
    public:
        /**
        * @brief Constructor that creates a ClusteringPopulationSelector object from the given parameters.
        * @param graph A pointer to the underlying graph object.
        * @param populationPtr A pointer to the underlying population.
        * @param predictedClusterCount The predicted cluster count.
        * @param clusterGenerationFunction The clusterGenerationFunction index.
        * @param threadCount The threadCount.
        */
        ClusteringPopulationSelector(const AbstractGraph* graph,
                                     EncodingFitnessDataStructure* populationPtr,
                                     uint64_t predictedClusterCount,
                                     uint32_t clusterGenerationFunction,
                                     const size_t threadCount = 1);

        /**
        * @brief standard destructor
        */
        ~ClusteringPopulationSelector();

        /**
        * @brief Selects the given population.
        * @return void
        */
        void selectPopulation();
    protected:
    private:
        /**
        * @brief Selects the given sub population.
        * @return void
        */
        void selectSubPopulation(size_t populationIndexBegin, size_t populationIndexEnd, size_t threadID);

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
        * @var predictedClusterCount
        * @brief The predicted cluster count.
        */
        uint64_t predictedClusterCount;

        /**
        * @var clusterGenerationFunction
        * @brief The clusterGenerationFunction index.
        */
        uint32_t clusterGenerationFunction;
};

template<class EncodingFitnessDataStructure>
ClusteringPopulationSelector<EncodingFitnessDataStructure>::ClusteringPopulationSelector(
    const AbstractGraph* graph,
    EncodingFitnessDataStructure* populationPtr,
    uint64_t predictedClusterCount,
    uint32_t clusterGenerationFunction,
    const size_t threadCount)
{
    this->graph = graph;
    this->populationPtr = populationPtr;
    this->predictedClusterCount = predictedClusterCount;
    this->clusterGenerationFunction = clusterGenerationFunction;
    this->threadCount = threadCount;
}

template<class EncodingFitnessDataStructure>
ClusteringPopulationSelector<EncodingFitnessDataStructure>::~ClusteringPopulationSelector()
{

}

template<class EncodingFitnessDataStructure>
void ClusteringPopulationSelector<EncodingFitnessDataStructure>::selectPopulation()
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
                                        &ClusteringPopulationSelector<EncodingFitnessDataStructure>::selectSubPopulation,
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

template<class EncodingFitnessDataStructure>
void ClusteringPopulationSelector<EncodingFitnessDataStructure>::selectSubPopulation(
    size_t populationIndexBegin,
    size_t populationIndexEnd,
    size_t threadID)
{
    IntegerEncodingInitializer initializer(this->graph, this->predictedClusterCount, this->clusterGenerationFunction);
    for (size_t i = populationIndexBegin; i < populationIndexEnd - 1; i++)
    {
        if ((*this->populationPtr)[i].populationEncoding.getEncoding() == (*this->populationPtr)[i + 1].populationEncoding.getEncoding())
        {
            (*this->populationPtr)[i].populationEncoding = initializer.getRandomSolution();
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
