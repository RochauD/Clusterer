/**
* @file ClusterRefiner.cpp
* @brief cluster refiner interface implementation
*/

//external headers
#include <iostream>
//local headers
#include "../include/ClusterRefiner.hpp"


namespace clusterer
{
namespace backend
{

ClusterRefiner::ClusterRefiner(std::mt19937 *rand_gen, double prob)
: gen(rand_gen), bd(prob)
{
   // this->gen = rand_gen;
    //bd = std::bernoulli_distribution(prob);
}

void ClusterRefiner::refine(ClusterEncoding& clusterSol, const AbstractGraph& graph)
{
	uint32_t cluster_number = clusterSol.getClusterCount();
    clusters_density = std::vector<double>(cluster_number,0.0);

    computeClustersDensity(clusterSol,graph);
    ClusterEncoding::Encoding cluster = clusterSol.getEncoding();
    
    std::vector<int> cluster_list_freq(cluster.size(),0);

    // build frequency list of cluster ids
    for(unsigned int i = 0; i < cluster.size(); i++){
        cluster_list_freq[clusterSol.getClusterOfVertex(i)]++;
    }

    double max_cluster_den = clusters_density[0];
    ClusterId max_cluster_id = 0;
    double min_cluster_den = clusters_density[0];
    ClusterId min_cluster_id = 0;

    for(unsigned int i = 0; i < clusters_density.size(); i++){
    	if(cluster_list_freq[i] != 0){
            std::cout<<"cluster: "<<i<<"; density: "<<clusters_density[i]<<"\n";
    		if(clusters_density[i] >= max_cluster_den){
                max_cluster_den = clusters_density[i];
                max_cluster_id = i;
    		}
    		if(clusters_density[i] <= min_cluster_den){
    			min_cluster_den = clusters_density[i];
    			min_cluster_id = i;
    		}
    	}
    }

    ClusterId cluster_to_refine;
    if(bd((*gen))) cluster_to_refine = max_cluster_id;
    else cluster_to_refine = min_cluster_id;
 
    IntegerVectorEncoding option1(&graph);
    IntegerVectorEncoding option2(&graph);

    for(auto& e: graph.getEdgesAndWeights()){
    	ClusterId startNodeCluster = clusterSol.getClusterOfVertex(e.first.first);
        ClusterId endNodeCluster = clusterSol.getClusterOfVertex(e.first.second);
     	if(startNodeCluster == cluster_to_refine 
     		&& endNodeCluster != cluster_to_refine){
     		option1.addToCluster(e.first.first,endNodeCluster);
     	    option2.addToCluster(e.first.second,startNodeCluster);
     	}
    }

    double option1_den = getClusterDensity(cluster_to_refine,option1,graph);
    double option2_den = getClusterDensity(cluster_to_refine,option2,graph);
    double original = getClusterDensity(cluster_to_refine,clusterSol,graph);
    
    if(std::max(std::max(option1_den,option2_den),original) == option1_den)
    {
        for(unsigned int i = 0; i < cluster.size();i++){
        	ClusterId c = option1.getClusterOfVertex(i);
        	if(c == clusterSol.getClusterOfVertex(i)) 
        		clusterSol.addToCluster(i,c);
        }
    } else if (std::max(std::max(option1_den,option2_den),original) == option2_den)
    {
        for(unsigned int i = 0; i < cluster.size();i++){
        	ClusterId c = option2.getClusterOfVertex(i);
        	if(c == clusterSol.getClusterOfVertex(i)) 
        		clusterSol.addToCluster(i,c);
        }
    	
    }
}

void ClusterRefiner::computeClustersDensity(ClusterEncoding& clusterSol,
            const AbstractGraph& graph)
{

    //std::vector<VertexId> vertices = clusterSol.getVerticesInCluster(cid);
    //double number_of_vertices = vertices.size();

    for (auto& e : graph.getEdgesAndWeights()){
    	ClusterId startNodeCluster = clusterSol.getClusterOfVertex(e.first.first);
        ClusterId endNodeCluster = clusterSol.getClusterOfVertex(e.first.second);
        // the if basically checks if edge e is in a cluster
        if(startNodeCluster == endNodeCluster){
            clusters_density[startNodeCluster] += e.second;
        }
    }

    for (unsigned int i = 0; i < clusters_density.size(); i++){
        double no_of_vertices = clusterSol.getVerticesInCluster(i).size();
        if(no_of_vertices != 0)
            clusters_density[i] = clusters_density[i]/(no_of_vertices*no_of_vertices);
    }

}

double ClusterRefiner::getClusterDensity(ClusterId cid, ClusterEncoding& clusterSol,
            const AbstractGraph& graph)
{
    double no_vertices = clusterSol.getVerticesInCluster(cid).size();

    //std::vector<VertexId> vertices = clusterSol.getVerticesInCluster(cid);
    //double number_of_vertices = vertices.size();

    double weight = 0.0;
    for (auto& e : graph.getEdgesAndWeights()){
    	ClusterId startNodeCluster = clusterSol.getClusterOfVertex(e.first.first);
        ClusterId endNodeCluster = clusterSol.getClusterOfVertex(e.first.second);
        // the if basically checks if edge e is in cluster cid
        if(startNodeCluster == endNodeCluster && startNodeCluster == cid){
            weight += e.second;
        }
    }

    return weight/(no_vertices*no_vertices);

}



ClusterRefiner::~ClusterRefiner()
{
	//dtor
}

}
}