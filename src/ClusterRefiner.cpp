/**
* @file ClusterRefiner.cpp
* @brief cluster refiner interface implementation
*/

//external headers
// uncomment if the prints are needed #include <iostream>
//local headers
#include "../include/ClusterRefiner.hpp"


namespace clusterer
{
namespace backend
{

void ClusterRefiner::printSol(const ClusterEncoding& clusterSol)
{
    /*
    for(unsigned int i = 0; i < clusterSol.size(); i++){
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
    */
}

ClusterRefiner::ClusterRefiner(std::mt19937* rand_gen, double prob)
    : gen(rand_gen), bd(prob)
{
    this->after_density = 0.0;
    this->original_density = 0.0;
}

void ClusterRefiner::refine(ClusterEncoding& clusterSol, const AbstractGraph& graph)
{
    // initialize clusters_density vector and populate with the
    // computed values in computeClustersDensity function
    uint32_t cluster_number = clusterSol.size();
    clusters_density = std::vector<double>(cluster_number,0.0);
    computeClustersDensity(clusterSol,graph);

    std::vector<int> cluster_list_freq(clusterSol.size(),0);

    // build frequency list of cluster ids needed for a check down below
    for (unsigned int i = 0; i < clusterSol.size(); i++)
    {
        cluster_list_freq[clusterSol.getClusterOfVertex(i)]++;
    }

    double max_cluster_den = clusters_density[0];
    ClusterId max_cluster_id = 0;
    double min_cluster_den = RAND_MAX;
    ClusterId min_cluster_id = 0;

    for (unsigned int i = 0; i < clusters_density.size(); i++)
    {
        if (cluster_list_freq[i] != 0)
        {
            // check if needed the computed density values for the clusters
            // std::cout<<i<<": "<<"--> "<<clusters_density[i]<<"\n";

            if (clusters_density[i] >= max_cluster_den)
            {
                max_cluster_den = clusters_density[i];
                max_cluster_id = i;
            }
            if (clusters_density[i] <= min_cluster_den)
            {
                min_cluster_den = clusters_density[i];
                min_cluster_id = i;
            }
        }
    }

    // pick which cluster to refine using bernoulli distribution
    // p -- probability to refine max_cluster_id
    // (1-p) -- probability to refine min_cluster_id
    ClusterId cluster_to_refine;
    if (bd((*gen))) { cluster_to_refine = max_cluster_id; }
    else { cluster_to_refine = min_cluster_id; }

    // create the 2 new possible encodings
    // option1: if an edge is in between clusters the node from the
    // cluster to be refined is placed in the other cluster
    // option2: if an edge is in between clusters the node from the
    // the other cluster is placed in the to be refined cluster

    IntegerVectorEncoding option1(&graph);
    IntegerVectorEncoding option2(&graph);

    // make option1, option2 copies of the original solution
    for (unsigned int i = 0; i < clusterSol.size(); i++)
    {
        ClusterId temp = clusterSol.getClusterOfVertex(i);
        option1.addToCluster(i,temp);
        option2.addToCluster(i,temp);
    }

    printSol(option1);

    for (auto& e: graph.getEdgesAndWeights())
    {
        ClusterId startNodeCluster = clusterSol.getClusterOfVertex(e.first.first);
        ClusterId endNodeCluster = clusterSol.getClusterOfVertex(e.first.second);
        if (startNodeCluster == cluster_to_refine
                && endNodeCluster != cluster_to_refine)
        {

            option1.addToCluster(e.first.first,endNodeCluster);
            option2.addToCluster(e.first.second,startNodeCluster);
        }
    }

    // finding the intra-cluster density corresponding to the new cluster
    // for the 2 new options and store the original's density
    double option1_den = getClusterDensity(cluster_to_refine,option1,graph);
    double option2_den = getClusterDensity(cluster_to_refine,option2,graph);
    this->original_density = clusters_density[cluster_to_refine];
    this->after_density = this->original_density;

    /* in case future debugging is needed this would be helpful
    std::cout<<"original: "; printSol(clusterSol);
    std::cout<<cluster_to_refine<<": density -- "<<original<<"\n";

    std::cout<<"option1: "; printSol(option1);
    std::cout<<cluster_to_refine<<": density -- "<<option1_den<<"\n";

    std::cout<<"option2: "; printSol(option2);
    std::cout<<cluster_to_refine<<": density -- "<<option2_den<<"\n";
    */

    // update the original version considering the bigger intra-cluster
    // density for the refined chosen cluster
    // or it can stay the same if better improvements are not made
    if (std::max(std::max(option1_den,option2_den),this->original_density) == option1_den)
    {
        this->after_density = option1_den;
        for (unsigned int i = 0; i < clusterSol.size(); i++)
        {
            ClusterId c = option1.getClusterOfVertex(i);
            if (c != clusterSol.getClusterOfVertex(i))
            { clusterSol.addToCluster(i,c); }
        }
    }
    else if (std::max(std::max(option1_den,option2_den),this->original_density) == option2_den)
    {
        this->after_density = option2_den;
        for (unsigned int i = 0; i < clusterSol.size(); i++)
        {
            ClusterId c = option2.getClusterOfVertex(i);
            if (c != clusterSol.getClusterOfVertex(i))
            { clusterSol.addToCluster(i,c); }
        }

    }

    clusterSol.normalize();
}

void ClusterRefiner::computeClustersDensity(ClusterEncoding& clusterSol,
        const AbstractGraph& graph)
{
    // compute the total intra weight of each cluster and store it
    // properly into clusters_density[respective_cluster]

    for (auto& e : graph.getEdgesAndWeights())
    {
        ClusterId startNodeCluster = clusterSol.getClusterOfVertex(e.first.first);
        ClusterId endNodeCluster = clusterSol.getClusterOfVertex(e.first.second);
        // the if basically checks if edge e is in a cluster
        if (startNodeCluster == endNodeCluster)
        {
            clusters_density[startNodeCluster] += e.second;
        }
    }

    // for each cluster Id find out the number of vertices in the cluster
    // if cluster Id has no vertices it's density will stay 0.0
    for (unsigned int i = 0; i < clusters_density.size(); i++)
    {
        double no_of_vertices = clusterSol.getVerticesInCluster(i).size();
        if (no_of_vertices != 0)
        { clusters_density[i] = clusters_density[i]/(no_of_vertices*no_of_vertices); }
    }

}

double ClusterRefiner::getClusterDensity(ClusterId cid, ClusterEncoding& clusterSol,
        const AbstractGraph& graph)
{
    double no_vertices = clusterSol.getVerticesInCluster(cid).size();

    // the cluster cid was basically replaced by another clusterId
    // this can happen
    // no point in carrying on and compute its density
    if (no_vertices == 0) { return 0; }

    double weight = 0.0;
    for (auto& e : graph.getEdgesAndWeights())
    {
        ClusterId startNodeCluster = clusterSol.getClusterOfVertex(e.first.first);
        ClusterId endNodeCluster = clusterSol.getClusterOfVertex(e.first.second);
        // the if basically checks if edge e is in cluster cid
        if (startNodeCluster == endNodeCluster && startNodeCluster == cid)
        {
            weight += e.second;
        }
    }

    return weight/(no_vertices*no_vertices);

}

// again these are useful for the testing units, not part of the algorithm itself
double ClusterRefiner::getOriginalClusterRefineDensity()
{
    return this->original_density;
}

double ClusterRefiner::getAfterClusterRefineDensity()
{
    return this->after_density;
}

ClusterRefiner::~ClusterRefiner()
{
    //dtor
}

}
}