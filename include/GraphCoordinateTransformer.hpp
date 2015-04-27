/**
 * @file GraphCoordinateTransformer.hpp
 * @brief implementation of a transformer to obtain coordinates for a graph's nodes
 * using the edge's weights
 */
#ifndef CLUSTERER_FRONTEND_GRAPH_COORD_TRANS_HPP
#define CLUSTERER_FRONTEND_GRAPH_COORD_TRANS_HPP

 // standard headers
#include <stdint.h>
#include <map>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

// internal headers
#include "ClusterEncoding.hpp"
#include "IntegerVectorEncoding.hpp"
#include "AbstractGraph.hpp"
#include "Graph.hpp"

//using namespace clb;

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace frontend is the namespace for all backend components of the
* project.
*/
namespace frontend
{

class GraphCoordinateTransformer{

    public:
        /**
        * @brief constructor which applies the MDS algorithm
        * @param takes a graph reference to which the algorithm is applied
        */
        GraphCoordinateTransformer(const backend::AbstractGraph& g);

        /**
        * @brief getter to obtain the constructed map
        * @return map of the type <vertex id, pair of coordinates>
        */
        std::map<backend::VertexId,std::pair<double,double>> getCoordinateMap();
        
        /**
        * @brief normalizes the already obtained coordinates from the MSD algorithm
        * @param height 
        * @param width
        * @return the normalized map 
        */
        std::map<backend::VertexId,std::pair<double,double>> 
        getNormalizedMap(uint64_t height, uint64_t width, uint64_t offset = 5);

        /**
        * @brief empty destructor
        */
        ~GraphCoordinateTransformer();

    private:
        
        std::map<backend::VertexId,std::pair<double,double>> map_coord;

        /**
        * @brief function to compare in descending order 2 pairs
        * @param first pair object
        * @param second pair object
        * @return boolean
        */
        static bool pairCompare(const std::pair<double, uint64_t>&,
 const std::pair<double, uint64_t>&);

};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clf = clusterer::frontend;

#endif