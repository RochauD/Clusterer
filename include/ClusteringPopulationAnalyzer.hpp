/**
* @file ClusteringPopulationAnalyzer.hpp
* @brief In this file the class ClusteringPopulationAnalyzer is defined. This class is used to
* analyze the fitness of a clustering solution population.
*/
#ifndef CLUSTERER_BACKEND_CLUSTERING_POPULATION_ANALYZER_HPP
#define CLUSTERER_BACKEND_CLUSTERING_POPULATION_ANALYZER_HPP

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
* @class ClusteringPopulationAnalyzer
* @brief Class which assess the quality of a clustering solution population.
* @tparam ClusteringSolutionAnalyzerFunction The function used to analyze a member of the population.
* The ClusteringSolutionAnalyzerFunction type needs to have a function with the following prototype:
* FitnessType analyze(EncodingType*, AbstractGraph*)
* @tparam EncodingFitnessDataStructure The data structure which represents a population.
*/
template<class ClusteringSolutionAnalyzerFunction, class EncodingFitnessDataStructure>
class ClusteringPopulationAnalyzer
{
    public:
        /**
        * @brief standard constructor
        */
        ClusteringPopulationAnalyzer(const AbstractGraph* graph, EncodingFitnessDataStructure* populationPtr, const size_t threadCount = 1);

        /**
        * @brief standard destructor
        */
        ~ClusteringPopulationAnalyzer();

        /**
        * @brief Evaluates the given population.
        * @return void
        */
        void evaluatePopulation();
    protected:
    private:
        /**
        * @brief Evaluates the given sub population.
        * @return void
        */
        void evaluateSubPopulation(size_t populationIndexBegin, size_t populationIndexEnd);

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
};

template<class ClusteringSolutionAnalyzerFunction, class EncodingFitnessDataStructure>
ClusteringPopulationAnalyzer<ClusteringSolutionAnalyzerFunction, EncodingFitnessDataStructure>::ClusteringPopulationAnalyzer(const AbstractGraph* graph, EncodingFitnessDataStructure* populationPtr, const size_t threadCount)
{
    this->graph = graph;
    this->populationPtr = populationPtr;
    this->threadCount = threadCount;
}

template<class ClusteringSolutionAnalyzerFunction, class EncodingFitnessDataStructure>
ClusteringPopulationAnalyzer<ClusteringSolutionAnalyzerFunction, EncodingFitnessDataStructure>::~ClusteringPopulationAnalyzer()
{

}

template<class ClusteringSolutionAnalyzerFunction, class EncodingFitnessDataStructure>
void ClusteringPopulationAnalyzer<ClusteringSolutionAnalyzerFunction, EncodingFitnessDataStructure>::evaluatePopulation()
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
        threadPool.push_back(std::thread(&ClusteringPopulationAnalyzer<ClusteringSolutionAnalyzerFunction, EncodingFitnessDataStructure>::evaluateSubPopulation, this, populationIndexBegin, populationIndexEnd));
        populationIndexBegin = populationIndexEnd;
    }

    // get and combine result
    for (auto& thread : threadPool)
    {
        thread.join();
    }
}

template<class ClusteringSolutionAnalyzerFunction, class EncodingFitnessDataStructure>
void ClusteringPopulationAnalyzer<ClusteringSolutionAnalyzerFunction, EncodingFitnessDataStructure>::evaluateSubPopulation(size_t populationIndexBegin, size_t populationIndexEnd)
{
    ClusteringSolutionAnalyzerFunction analyzer;
    for (size_t i = populationIndexBegin; i < populationIndexEnd; i++)
    {
        if ((*this->populationPtr)[i].modified)
        {
            (*this->populationPtr)[i].fitnessValue = analyzer.analyze(&((*this->populationPtr)[i].populationEncoding), this->graph);
            (*this->populationPtr)[i].modified = false;
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
