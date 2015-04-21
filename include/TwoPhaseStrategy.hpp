/**
 * @file TwoPhaseStrategy.hpp
 * @brief genetic strategy implementation
 */
#ifndef CLUSTERER_BACKEND_TWO_PHASE_STRATEGY_HPP
#define CLUSTERER_BACKEND_TWO_PHASE_STRATEGY_HPP

// standard headers
#include <stdint.h>
#include <atomic>
// external headers

// internal headers
#include "ClusterEncoding.hpp"
#include "AbstractGraph.hpp"
#include "GeneticStrategy.hpp"
#include "ClusteringParams.hpp"
#include "ConcurrentLockingQueue.hpp"
#include "FitnessAnalyzer.hpp"
#include "ClusteringPopulationAnalyzer.hpp"
#include "PopulationMutatorEngine.hpp"
#include "PopulationCrossoverEngine.hpp"
#include "CombinedCrossoverEngine.hpp"
#include "CombinedMutation.hpp"
#include "Selector.hpp"
#include "GlobalFileLogger.hpp"

#include <fstream>

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

template<class Encoding, class EncodingInitalizer>
class TwoPhaseStrategy
{
    public:
        /**
         * @brief Create a TwoPhaseStrategy based on a graph and parameters
         * @param graph The graph on which the strategy is based
         * @param clusteringParams The clustering parameters
         */
        TwoPhaseStrategy(const AbstractGraph* graph,
                         const ClusteringParams clusteringParameters,
                         std::vector<std::pair<Encoding, double>>* population,
                         clc::ConcurrentLockingQueue<std::pair<Encoding, double>>* outQueue);

        /**
         * @brief obtain the next generation of the clustering solution
         * @return void
         */
        void runAlgorithm(bool restart = true);

        void stopAlgorithm();
        void resumeAlgorithm();

        ~TwoPhaseStrategy();

    protected:
        const AbstractGraph* graph;
        ClusteringParams clusteringParameters;
        std::atomic<bool> stopFlag;
        std::vector<std::pair<Encoding, double>>* population;
        clc::ConcurrentLockingQueue<std::pair<Encoding, double>>* outQueue;
        uint64_t iterationCount;
        double currentMaxFitness;
        bool currentPhase;

    private:
        void initalizePopulation();
        bool checkRunningConditions();
        bool checkForPhaseSwitch();
        void sortPopulation();

};

template<class Encoding, class EncodingInitalizer>
TwoPhaseStrategy<Encoding, EncodingInitalizer>::TwoPhaseStrategy(const AbstractGraph* graph,
        const ClusteringParams clusteringParameters,
        std::vector<std::pair<Encoding, double>>* population,
        clc::ConcurrentLockingQueue<std::pair<Encoding, double>>* outQueue)
{
    this->graph = graph;
    this->clusteringParameters = clusteringParameters;
    this->population = population;
    this->outQueue = outQueue;
    this->stopFlag = false;
    this->iterationCount = 0;
    this->currentMaxFitness = 0.0;
    this->currentPhase = false;
}

template<class Encoding, class EncodingInitalizer>
TwoPhaseStrategy<Encoding, EncodingInitalizer>::~TwoPhaseStrategy()
{

}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::runAlgorithm(bool restart)
{
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm run started");
    // set up

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<std::pair<Encoding, double>>> populationFitnessAnalyzer(
        this->graph,
        this->population,
        this->clusteringParameters.threadCount);
    PopulationMutatorEngine<std::vector<std::pair<Encoding, double>>, CombinedMutation> populationExplorationMutatorEngine(
                this->graph,
                this->population,
                this->clusteringParameters.explorationMutationChance,
                this->clusteringParameters.threadCount);
    PopulationCrossoverEngine<std::vector<std::pair<Encoding, double>>, Encoding, CombinedCrossoverEngine, Selector<std::vector<std::pair<Encoding, double>>>> populationCrossoverEngine(
                this->graph,
                this->population,
                this->clusteringParameters.crossoverIterationCount,
                this->clusteringParameters.threadCount);

    // @todo check for valid parameters!
    // if not restart then make usre populaion exists

    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Initalized helper classes");
    // reset if needed
    if (restart)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Resetting Population");
        this->initalizePopulation();
        this->iterationCount = 0;
        this->currentMaxFitness = 0.0;
    }
    populationFitnessAnalyzer.evaluatePopulation();
    this->sortPopulation();
    this->currentMaxFitness = (*this->population)[0].second;

    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Starting in exploration phase");
    // main algorithmic loop
    while (this->checkRunningConditions())
    {
        if (false)//this->currentPhase)
        {
            // refinement phase
            populationExplorationMutatorEngine.mutatePopulation();
        }
        else
        {
            // exploration phase
            populationCrossoverEngine.crossoverPopulation();
            populationExplorationMutatorEngine.mutatePopulation();
            if (false)//this->checkForPhaseSwitch())
            {
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Switched to refinement phase.");
                this->currentPhase = true;
            }
        }
        populationFitnessAnalyzer.evaluatePopulation();
        this->sortPopulation();
        this->currentMaxFitness = (*this->population)[0].second;
        if (this->population->size() > this->clusteringParameters.maxPopulationSize)
        {
            this->population->resize(this->clusteringParameters.maxPopulationSize);
        }

        // log our progress
        if (iterationCount % this->clusteringParameters.logFrequency == 0)
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Iteration: ",
                                                   this->iterationCount,
                                                   " Current maximal fitness: ",
                                                   this->currentMaxFitness);
        }
        this->iterationCount++;
    }
    // log end of algorithm
    if (this->stopFlag)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm was stopped.");
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm finished. The maximal fitness is: ", this->currentMaxFitness);
    }

    // print output
    std::ofstream file("file.txt");
    for (auto& e : (*this->population))
    {
        for (auto& p : e.first.getEncoding())
        {
            file << p << " ";
        }
        file << "\n";
    }
    file.close();
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::stopAlgorithm()
{
    this->stopFlag = true;
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::resumeAlgorithm()
{
    this->stopFlag = false;
}


template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::initalizePopulation()
{
    // resize population if necessary
    if (this->population->size() < this->clusteringParameters.minPopulationSize ||
            this->population->size() > this->clusteringParameters.maxPopulationSize)
    {
        this->population->reserve(this->clusteringParameters.maxPopulationSize);
        this->population->resize(this->clusteringParameters.minPopulationSize);
    }
    EncodingInitalizer encodingInitalizer(this->graph);
    for (auto& e : *this->population)
    {
        e = std::make_pair(encodingInitalizer.getRandomSolution(), 0.0);
    }
}

template<class Encoding, class EncodingInitalizer>
bool TwoPhaseStrategy<Encoding, EncodingInitalizer>::checkRunningConditions()
{
    return (!this->stopFlag &&
            this->iterationCount <= this->clusteringParameters.maxIterations &&
            this->currentMaxFitness <= this->clusteringParameters.maxFitness &&
            (this->iterationCount <= this->clusteringParameters.minIterations ||
             this->currentMaxFitness <= this->clusteringParameters.minFitness));
}

template<class Encoding, class EncodingInitalizer>
bool TwoPhaseStrategy<Encoding, EncodingInitalizer>::checkForPhaseSwitch()
{
    return (this->iterationCount >= this->clusteringParameters.phaseSwitchIterationValue ||
            this->currentMaxFitness >= this->clusteringParameters.phaseSwitchFitnessValue);
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::sortPopulation()
{
    std::sort(this->population->begin(), this->population->end(),
              [=](const std::pair<Encoding, double>& v1, const std::pair<Encoding, double>& v2)->bool
    {
        return v1.second > v2.second;
    });
}

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
