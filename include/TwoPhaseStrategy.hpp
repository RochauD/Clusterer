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
#include "ClusteringParams.hpp"
#include "ConcurrentLockingQueue.hpp"
#include "FitnessAnalyzer.hpp"
#include "ClusteringPopulationAnalyzer.hpp"
#include "PopulationMutatorEngine.hpp"
#include "PopulationCrossoverEngine.hpp"
#include "CombinedCrossoverEngine.hpp"
#include "CombinedMutation.hpp"
#include "ClusteringPopulationRefiner.hpp"
#include "ClusteringPopulationSelector.hpp"
#include "ClusterRefiner.hpp"
#include "Selector.hpp"
#include "GlobalFileLogger.hpp"
#include "PopulationMember.hpp"
#include "PopulationExporter.hpp"

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
        * @brief Standard Constructor for a TwoPhaseStrategy which can cluster a graph.
        */
        TwoPhaseStrategy();

        /**
         * @brief Create a TwoPhaseStrategy which can cluster a graph.
         * @param graph The graph on which the strategy is based
         * @param clusteringParams The clustering parameters
         * @param population A pointer to a population
         * @param outQueue A pointer to an output queue.
         */
        TwoPhaseStrategy(const AbstractGraph* graph,
                         ClusteringParams clusteringParameters,
                         std::vector<PopulationMember<Encoding, double>>* population,
                         clc::ConcurrentLockingQueue<std::pair<PopulationMember<Encoding, double>, uint64_t>>* outQueue);


        void setGraph(const AbstractGraph* graph);
        void setClusteringParameters(ClusteringParams clusteringParameters);
        void setPopulation(std::vector<PopulationMember<Encoding, double>>* population);
        void setOutQueue(clc::ConcurrentLockingQueue<std::pair<PopulationMember<Encoding, double>, uint64_t>>* outQueue);


        /**
         * @brief obtain the next generation of the clustering solution
         * @return void
         */
        bool runAlgorithm(bool restart = true);

        void stopAlgorithm();
        void resumeAlgorithm();

        ~TwoPhaseStrategy();

    protected:
        const AbstractGraph* graph;
        ClusteringParams clusteringParameters;
        std::atomic<bool> stopFlag;
        std::vector<PopulationMember<Encoding, double>>* population;
        clc::ConcurrentLockingQueue<std::pair<PopulationMember<Encoding, double>, uint64_t>>* outQueue;
        uint64_t iterationCount;
        uint64_t lastIterationWithChangedFitness;
        PopulationMember<Encoding, double> currentBest;
        bool currentPhase;

    private:
        void initalizePopulation();
        bool checkRunningConditions();
        bool checkForPhaseSwitch();
        bool checkInitalizationCondition();
        void sortPopulation();

};


template<class Encoding, class EncodingInitalizer>
TwoPhaseStrategy<Encoding, EncodingInitalizer>::TwoPhaseStrategy()
{
    this->graph = nullptr;
    this->population = nullptr;
    this->outQueue = nullptr;
    this->stopFlag = false;
    this->iterationCount = 0;
    this->currentPhase = false;
    this->lastIterationWithChangedFitness = 0;
}

template<class Encoding, class EncodingInitalizer>
TwoPhaseStrategy<Encoding, EncodingInitalizer>::TwoPhaseStrategy(const AbstractGraph* graph,
        ClusteringParams clusteringParameters,
        std::vector<PopulationMember<Encoding, double>>* population,
        clc::ConcurrentLockingQueue<std::pair<PopulationMember<Encoding, double>, uint64_t>>* outQueue)
{
    this->graph = graph;
    this->clusteringParameters = clusteringParameters;
    this->population = population;
    this->outQueue = outQueue;
    this->stopFlag = false;
    this->iterationCount = 0;
    this->currentPhase = false;
    this->lastIterationWithChangedFitness = 0;
}

template<class Encoding, class EncodingInitalizer>
TwoPhaseStrategy<Encoding, EncodingInitalizer>::~TwoPhaseStrategy()
{

}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::setGraph(const AbstractGraph* graph)
{
    this->graph = graph;
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::setClusteringParameters(ClusteringParams clusteringParameters)
{
    this->clusteringParameters = clusteringParameters;
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::setPopulation(std::vector<PopulationMember<Encoding, double>>* population)
{
    this->population = population;
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::setOutQueue(clc::ConcurrentLockingQueue<std::pair<PopulationMember<Encoding, double>, uint64_t>>* outQueue)
{
    this->outQueue = outQueue;
}

template<class Encoding, class EncodingInitalizer>
bool TwoPhaseStrategy<Encoding, EncodingInitalizer>::runAlgorithm(bool restart)
{
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm run started");

    // check conditions
    if (this->checkInitalizationCondition() == false)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm run stopped. Parameters are invalid");
        return false;
    }
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm parameters are valid");

    // set up
    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<PopulationMember<Encoding, double>>> populationFitnessAnalyzer(
        this->graph,
        this->population,
        this->clusteringParameters.threadCount);
    ClusteringPopulationAnalyzer<MQAnalyzer, std::vector<PopulationMember<Encoding, double>>> populationMQAnalyzer(
        this->graph,
        this->population,
        this->clusteringParameters.threadCount);
    ClusteringPopulationAnalyzer<PerformanceAnalyzer, std::vector<PopulationMember<Encoding, double>>> populationPerformanceAnalyzer(
        this->graph,
        this->population,
        this->clusteringParameters.threadCount);
    ClusteringPopulationRefiner<ClusterRefiner, std::vector<PopulationMember<Encoding, double>>> populationRefiner(
        this->graph,
        this->population,
        this->clusteringParameters.refinementMutationChance,
        this->clusteringParameters.maxMinDensityClusterProbability,
        this->clusteringParameters.threadCount);
    ClusteringPopulationSelector<std::vector<PopulationMember<Encoding, double>>> populationSelector(
        this->graph,
        this->population,
        this->clusteringParameters.predictedClusterCount,
        this->clusteringParameters.clusterGenerationFunction,
        this->clusteringParameters.threadCount);
    PopulationMutatorEngine<std::vector<PopulationMember<Encoding, double>>, CombinedMutation> populationExplorationMutatorEngine(
                this->graph,
                this->population,
                this->clusteringParameters.explorationMutationChance,
                this->clusteringParameters.threadCount);
    PopulationCrossoverEngine<std::vector<PopulationMember<Encoding, double>>, Encoding, CombinedCrossoverEngine, Selector<std::vector<PopulationMember<Encoding, double>>>> populationCrossoverEngine(
                this->graph,
                this->population,
                this->clusteringParameters.crossoverIterationCount,
                this->clusteringParameters.threadCount);

    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Initialized helper classes");
    // reset if needed
    if (restart || this->population->size() < 2)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Resetting Population");
        this->initalizePopulation();
        this->iterationCount = 0;
    }

    // evaluate fitness metric
    switch (this->clusteringParameters.fitnessFunction)
    {
        case 0:
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Using fitness function: Fitness");
            populationFitnessAnalyzer.evaluatePopulation();
            break;
        case 1:
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Using fitness function: MQ");
            populationMQAnalyzer.evaluatePopulation();
            break;
        case 2:
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Using fitness function: Performance");
            populationPerformanceAnalyzer.evaluatePopulation();
            break;
        default:
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Using default fitness function.");
            populationFitnessAnalyzer.evaluatePopulation();
            break;
    }
    this->sortPopulation();
    this->currentBest = (*this->population)[0];
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Initial Evaluation completed. Current Maximum Fitness: ", this->currentBest.fitnessValue);

    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Starting in exploration phase");
    // main algorithmic loop
    while (this->checkRunningConditions())
    {
        if (this->currentPhase)
        {
            // refinement phase
            populationRefiner.refinePopulation();
            populationCrossoverEngine.crossoverPopulation();
        }
        else
        {
            // exploration phase
            populationCrossoverEngine.crossoverPopulation();
            populationExplorationMutatorEngine.mutatePopulation();
            if (this->checkForPhaseSwitch())
            {
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Switched to refinement phase.");
                this->currentPhase = true;
            }
        }

        // evaluate fitness metric
        switch (this->clusteringParameters.fitnessFunction)
        {
            case 0:
                populationFitnessAnalyzer.evaluatePopulation();
                break;
            case 1:
                populationMQAnalyzer.evaluatePopulation();
                break;
            case 2:
                populationPerformanceAnalyzer.evaluatePopulation();
                break;
            default:
                populationFitnessAnalyzer.evaluatePopulation();
                break;
        }
        this->sortPopulation();
        // reduce the population to a relativley unique one if flag is set
        if (this->clusteringParameters.uniquePopulationSelection)
        {
            populationSelector.selectPopulation();
            // evaluate fitness metric once more as we changed things
            switch (this->clusteringParameters.fitnessFunction)
            {
                case 0:
                    populationFitnessAnalyzer.evaluatePopulation();
                    break;
                case 1:
                    populationMQAnalyzer.evaluatePopulation();
                    break;
                case 2:
                    populationPerformanceAnalyzer.evaluatePopulation();
                    break;
                default:
                    populationFitnessAnalyzer.evaluatePopulation();
                    break;
            }
            this->sortPopulation();
        }

        // set new best
        if (this->currentBest.fitnessValue != (*this->population)[0].fitnessValue)
        {
            this->lastIterationWithChangedFitness = this->iterationCount;
        }
        this->currentBest = (*this->population)[0];
        // remove worst members
        if (this->population->size() > this->clusteringParameters.maxPopulationSize)
        {
            this->population->resize(this->clusteringParameters.maxPopulationSize);
        }

        // send our progress into queue
        if (iterationCount % this->clusteringParameters.enqueueFrequency == 0)
        {
            this->outQueue->push(std::make_pair((*this->population)[0],this->iterationCount));
        }
        // log our progress
        if (iterationCount % this->clusteringParameters.logFrequency == 0)
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Iteration: ",
                                                   this->iterationCount,
                                                   " Current maximal fitness: ",
                                                   this->currentBest.fitnessValue);
        }

        // autosave our progress
        if (iterationCount % this->clusteringParameters.autoSavePopulationFrequency == 0)
        {
            PopulationExporter populationExporter;
            populationExporter.writePopulationToFile(this->population, "autosave.data");
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Auto save population to file.");
        }

        this->iterationCount++;
    }
    return true;
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
    EncodingInitalizer encodingInitalizer(this->graph, this->clusteringParameters.predictedClusterCount ,this->clusteringParameters.clusterGenerationFunction);
    for (auto& e : *this->population)
    {
        PopulationMember<Encoding,double> member;
        member.fitnessValue = 0.0;
        member.modified = true;
        member.populationEncoding = encodingInitalizer.getRandomSolution();
        e = member;
    }
}

template<class Encoding, class EncodingInitalizer>
bool TwoPhaseStrategy<Encoding, EncodingInitalizer>::checkRunningConditions()
{
    // log end of algorithm
    if (this->stopFlag)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm was stopped.");
        return false;
    }
    else if (this->iterationCount > this->clusteringParameters.maxIterations ||
             this->currentBest.fitnessValue > this->clusteringParameters.maxFitness ||
             (this->iterationCount > this->clusteringParameters.minIterations &&
              this->currentBest.fitnessValue > this->clusteringParameters.minFitness))
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm finished. The maximal fitness is: ", this->currentBest.fitnessValue);
        return false;
    }
    else if ((this->iterationCount - this->lastIterationWithChangedFitness) > this->clusteringParameters.iterationUntilMissingImprovementCausesInterruption)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "[ALG] Algorithm finished as the solution is not getting better. The maximal fitness is: ", this->currentBest.fitnessValue);
        return false;
    }
    return true;
}

template<class Encoding, class EncodingInitalizer>
bool TwoPhaseStrategy<Encoding, EncodingInitalizer>::checkForPhaseSwitch()
{
    return (this->iterationCount >= this->clusteringParameters.phaseSwitchIterationValue ||
            this->currentBest.fitnessValue >= this->clusteringParameters.phaseSwitchFitnessValue);
}

template<class Encoding, class EncodingInitalizer>
bool TwoPhaseStrategy<Encoding, EncodingInitalizer>::checkInitalizationCondition()
{
    if (this->graph == nullptr)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "[ALG] Graph is not initalized");
        return false;
    }
    if (this->population == nullptr)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "[ALG] Population is not initalized");
        return false;
    }
    if (this->outQueue == nullptr)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "[ALG] Output Queue is not initalized");
        return false;
    }
    if (this->graph->getEdgesAndWeights().size() == 0)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "[ALG] Empty graph");
        return false;
    }

    return true;
}

template<class Encoding, class EncodingInitalizer>
void TwoPhaseStrategy<Encoding, EncodingInitalizer>::sortPopulation()
{
    std::sort(this->population->begin(), this->population->end(),
              [=](const PopulationMember<Encoding, double>& v1, const PopulationMember<Encoding, double>& v2)->bool
    {
        if (v1.fitnessValue == v2.fitnessValue)
        {
            return v1.populationEncoding.getEncoding() > v2.populationEncoding.getEncoding();
        }
        return v1.fitnessValue > v2.fitnessValue;
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
