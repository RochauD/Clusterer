#ifndef _CONFIGURATION_MANAGER_HPP
#define _CONFIGURATION_MANAGER_HPP

// standard headers
#include <string>
#include <unordered_map>
// external headers

// internal headers
#include "ClusteringParams.hpp"
#include "ConfigurationReaderWriter.hpp"


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
	* @brief Sets the number of clusters one suspects.
	* @param predictedClusterCount The number of clusters.
	* @return void
	*/
	void setPredictedClusterCount(uint64_t predictedClusterCount);
	/**
	* @brief Sets the number of threads used in the computation.
	* @param threadCount The number of threads.
	* @return void
	*/
	void setThreadCount(uint32_t threadCount);

	/**
	* @brief Returns the clustering parameters.
	* @return The current clustering parameters.
	*/
	ClusteringParams getClusteringParams();
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
	* @brief Returns the predicted cluster count.
	* @return The predicted cluster count.
	*/
	uint64_t getPredictedClusterCount();
	/**
	* @brief Returns the number of threads that should be used in the 
	* computation of the algorithm.
	* @return The number of threads.
	*/
	uint32_t getThreadCount();

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

#endif
