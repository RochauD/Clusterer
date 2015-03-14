#ifndef CLUSTERING_PARAMS_HPP
#define CLUSTERING_PARAMS_HPP

/**
* @brief clustering parameters for social clustering
*/
struct ClusteringParams
{
	/**
	* @brief number of iterations after which to stop searching
	*/
	uint64_t maxIterations;

	uint64_t minIterations;

	uint64_t predictedClusterCount;

	uint64_t phaseSwitchFitnessValue;

	uint64_t phaseSwitchIterationValue;

	uint64_t threadCount;
	

	/**
	* @brief minimum fitness to reach in order to stop searching
	*/
	double minFitness;


}

#endif
