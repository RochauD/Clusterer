/**
* @file GraphCoordinateTransformer.cpp
* @brief graph coordinate transformer implementation
*/

//external headers
// uncomment if the prints are needed #include <iostream>
//local headers
#include "../include/GraphCoordinateTransformer.hpp"


namespace clusterer
{
namespace frontend
{

bool GraphCoordinateTransformer::pairCompare(const std::pair<double, uint64_t>& firstElem,
 const std::pair<double, uint64_t>& secondElem) {
  return firstElem.first > secondElem.first;

}

GraphCoordinateTransformer::GraphCoordinateTransformer(const backend::AbstractGraph& graph)
{
    uint64_t no_vertices = graph.getNoVertices();

    //initialize D to 0 matrix
    Eigen::MatrixXd D = Eigen::MatrixXd::Zero(no_vertices,no_vertices);
    
    // populate the matrix D
    for(auto& e : graph.getEdgesAndWeights()){
        D(e.first.first,e.first.second) = e.second;
    }

    //centering matrix J
    Eigen::MatrixXd J(no_vertices,no_vertices);
    J = Eigen::MatrixXd::Identity(no_vertices,no_vertices) 
        - (1.0/no_vertices)*Eigen::MatrixXd::Ones(no_vertices,no_vertices);

    // squared-distance matrix
    Eigen::MatrixXd S(no_vertices,no_vertices);
    // D.array()*D.array coefficient-wise multiplication and after the operation
    // converted back to matrix object
    S = (D.array()*D.array()).matrix();

    Eigen::MatrixXd Z(no_vertices,no_vertices);
    Z = -0.5*J*S*J;

    uint64_t dimensions = 2; // for a 2D representation

    // compute eigenvalues/eigenvectors
    Eigen::EigenSolver<Eigen::MatrixXd> es(Z);

    // no specific order for the eigenvalues
    // need to find the eigenvalues with the highest magnitude
    uint64_t no_eigenvals = es.eigenvalues().size();
    std::vector<std::pair<double,uint64_t>> ordered_evals;
    ordered_evals.reserve(no_eigenvals);
    
    for(unsigned int i = 0; i < no_eigenvals; i++){
        std::complex<double> C;
        C = es.eigenvalues().col(0)[i];
        ordered_evals.push_back(std::make_pair<double,uint64_t>(std::norm(C),i));
    }

    /* // --testing purposes --
    for(auto& el: ordered_evals){
        std::cout<<"norm: "<<el.first<<"; index: "<<el.second<<"\n";
    }*/
    
    // order eigenvalues in descending order
    std::sort(ordered_evals.begin(),ordered_evals.end(),pairCompare);

    Eigen::MatrixXcd V(no_vertices,dimensions);
    Eigen::MatrixXcd Diag = Eigen::MatrixXcd::Zero(dimensions,dimensions);
    for(unsigned int i = 0; i < dimensions; i++){
        uint64_t index = ordered_evals[i].second;
        Diag(i,i) = es.eigenvalues().col(0)[index];
        V.col(i) = es.eigenvectors().col(index);
    }

    /* // -- testing purposes --
    std::cout<<"Diag -- chosen eigenvalues: \n"<<Diag<<"\n";
    std::cout<<"Respective eigenvector matrix: \n"<<V<<"\n";
    */

    Eigen::MatrixXcd Y(no_vertices,dimensions);
    Y = V*((Diag.array().sqrt()).matrix());

    // next transform Y ---> map_coord
    for(unsigned int i = 0; i < no_vertices; i++){
        double coord_x = std::real(Y.row(i)[0]);
        double coord_y = std::real(Y.row(i)[1]);
        map_coord[i] = std::make_pair(coord_x,coord_y);
    }
}

std::map<backend::VertexId,std::pair<double,double>> GraphCoordinateTransformer::getCoordinateMap()
{
    return map_coord;
}

GraphCoordinateTransformer::~GraphCoordinateTransformer()
{
    //empty dtor
}


}
}