/**
 * @file ConfigurationManager.hpp
 * @brief File in which the ConfigurationManager is defined.
 */
#ifndef CLUSTERER_BACKEND_CONFIGURATION_MANAGER_HPP
#define CLUSTERER_BACKEND_CONFIGURATION_MANAGER_HPP

// standard headers
#include <string>
#include <unordered_map>
// external headers

// internal headers
#include "ClusteringParams.hpp"
#include "ConfigurationReaderWriter.hpp"

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
* @class ConfigurationManager
* @brief Manages the configuration of the algorithm.
* @details The class ConfigurationManager is a proxy class that manages the
* algorithm parameters defined in the struct ClusteringParams. It provides
* setter and getter methods as well as the loading and saving of
* configuration parameters to files.
*/
class ConfigurationManager
{
    public:
        /**
        * @brief Default constructor for the ConfigurationManager.
        */
        ConfigurationManager();

        /**
        * @brief Default destructor for the ConfigurationManager.
        */
        ~ConfigurationManager();

        /**
        * @brief Sets the clustering parameters.
        * @param clusteringParams The clustering parameters which will be used.
        * @return void
        */
        void setClusteringParams(const ClusteringParams& clusteringParams);

        void setUniquePopulationSelection(bool uniquePopulationSelection);
        void setMaxMinDensityClusterProbability(double maxMinDensityClusterProbability);
        void setIterationUntilMissingImprovementCausesInterruption(uint64_t iterationUntilMissingImprovementCausesInterruption);
        void setEnqueueFrequency(uint64_t enqueueFrequency);

        /**
        * @brief Sets the log frequency.
        * @param logFrequency The log frequency.
        * @return void
        */
        void setLogFrequency(uint64_t logFrequency);

        /**
        * @brief Sets the exploration mutation chance.
        * @param explorationMutationChance The exploration mutation chance.
        * @return void
        */
        void setExplorationMutationChance(double explorationMutationChance);

        /**
        * @brief Sets the refinement mutation chance.
        * @param refinementMutationChance The refinement mutation chance.
        * @return void
        */
        void setRefinementMutationChance(double refinementMutationChance);

        /**
        * @brief Sets the crossover iteration count.
        * @param crossoverIterationCount The crossover iteration count.
        * @return void
        */
        void setCrossoverIterationCount(uint64_t crossoverIterationCount);

        /**
        * @brief Sets the minimum iteration population size.
        * @param minPopulationSize The value minimum population size.
        * @return void
        */
        void setMinPopulationSize(uint64_t minPopulationSize);

        /**
        * @brief Sets the maximum population size.
        * @param maxPopulationSize The maximum population size.
        * @return void
        */
        void setMaxPopulationSize(uint64_t maxPopulationSize);

        /**
        * @brief Sets the minimum iteration count.
        * @param minIterations The value of the minimum iteration count.
        * @return void
        */
        void setMinIterationsCount(uint64_t minIterations);

        /**
        * @brief Sets the maximum iteration count, on which the algorithm should
        * terminate.
        * @param maxIterations The value of the maximum iteration count.
        * @return void
        */
        void setMaxIterationsCount(uint64_t maxIterations);

        /**
        * @brief Sets the minimum fitness value, which is desired.
        * @param minFitness The value of the minimum Fitness.
        * @return void
        */
        void setMinFitness(double minFitness);

        /**
        * @brief Sets the maximum fitness value, on which the algorithm should
        * terminate.
        * @param maxFitness The value of the maximum Fitness.
        * @return void
        */
        void setMaxFitness(double maxFitness);

        /**
        * @brief Sets the fitness value, on which the algorithm should perform a
        * phase switch.
        * @param phaseSwitchFitnessValue The phase switch fitness value.
        * @return void
        */
        void setPhaseSwitchFitnessValue(double phaseSwitchFitnessValue);

        /**
        * @brief Sets the iteration value, on which the algorithm should perform a
        * phase switch.
        * @param phaseSwitchIterationValue The phase switch iteration value.
        * @return void
        */
        void setPhaseSwitchIterationValue(uint64_t phaseSwitchIterationValue);

        /**
        * @brief Sets the number of threads used in the computation.
        * @param threadCount The number of threads.
        * @return void
        */
        void setThreadCount(uint32_t threadCount);
	
	/**
        * @brief Selects the parameter for optimization.
        * @param fitnessFunction Choose 0 for fitness, 1 for MQ and 2 for Performance.
        * @return void
        */
        void setFitnessFunction(uint32_t fitnessFunction);
	
        /**
        * @brief Returns the clustering parameters.
        * @return The current clustering parameters.
        */
        ClusteringParams getClusteringParams();
	
        bool getUniquePopulationSelection();
        double getMaxMinDensityClusterProbability();
        uint64_t getIterationUntilMissingImprovementCausesInterruption();
        uint64_t getEnqueueFrequency();

        /**
        * @brief Gets the log frequency.
        * @param The log frequency.
        */
        uint64_t getLogFrequency();

        /**
        * @brief Gets the exploration mutation chance.
        * @param The exploration mutation chance.
        */
        double getExplorationMutationChance();

        /**
        * @brief Gets the refinement mutation chance.
        * @param The refinement mutation chance.
        */
        double getRefinementMutationChance();

        /**
        * @brief Gets the crossover iteration count.
        * @return The crossover iteration count.
        */
        uint64_t getCrossoverIterationCount();

        /**
        * @brief Returns the minimum population size.
        * @return The minimum population size
        */
        uint64_t getMinPopulationSize();

        /**
        * @brief Returns the maximum population size.
        * @return The maximum population size
        */
        uint64_t getMaxPopulationSize();

        /**
        * @brief Returns the minimum iteration count.
        * @return The minimum iteration count.
        */
        uint64_t getMinIterationsCount();

        /**
        * @brief Returns the maximum iteration count, on which the algorithm should
        * terminate.
        * @return The maximum iteration count.
        */
        uint64_t getMaxIterationsCount();

        /**
        * @brief Returns the minimum fitness value the algorithm should reach.
        * @return The minimum fitness value.
        */
        double getMinFitness();

        /**
        * @brief Returns the maximum fitness value, on which the algorithm should
        * terminate.
        * @return The maximum fitness value.
        */
        double getMaxFitness();

        /**
        * @brief Returns the phase switch fitness value threshold, on which the
        * algorithm should switch the phase.
        * @return The phase switch fitness value.
        */
        double getPhaseSwitchFitnessValue();

        /**
        * @brief Returns the phase switch iteration value threshold, on which the
        * algorithm should switch the phase.
        * @return The phase switch iteration value.
        */
        uint64_t getPhaseSwitchIterationValue();

        /**
        * @brief Returns the number of threads that should be used in the
        * computation of the algorithm.
        * @return The number of threads.
        */
        uint32_t getThreadCount();
	
	/**
        * @brief Selects the optimization method.
        * @return 0 for Fitness, 1 for MQ and 2 for Performance.
        */
        uint32_t getFitnessFunction();
	

        /**
        * @brief Loads clustering parameters from the specified file.
        * @param fullPathName The full path to a file. This should include both the
        * absolute or relative directory and the filename and file extension of the
        * file.
        * @return void
        * @throws std::runtime_error
        */
        void loadClusteringParams(const std::string& fullPathName);

        /**
        * @brief Save clustering parameters to the specified file.
        * @param fullPathName The full path to a file. This should include both the
        * absolute or relative directory and the filename and file extension of the
        * file.
        * @return void
        * @throws std::runtime_error
        */
        void saveClusteringParams(const std::string& fullPathName);
	

    protected:
    private:
        /**
        * @var clusteringParams
        * @brief Clustering parameters.
        * @details The member variable clusteringParams is the underlying data
        * structure which stores the parameters.
        */
        ClusteringParams clusteringParams;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
