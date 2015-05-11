/**
* @file GraphCoordinateTransformer.cpp
* @brief graph coordinate transformer implementation
*/

//external headers
// uncomment if the prints are needed 
#include <iostream>
//local headers
#include "../include/GraphCoordinateTransformer.hpp"
#include <utility>

#ifdef __unix
#define ARMA_64BIT_WORD
#endif

namespace clusterer
{
namespace frontend
{

bool GraphCoordinateTransformer::pairCompare(const std::pair<double, uint64_t>& firstElem,
        const std::pair<double, uint64_t>& secondElem)
{
    return firstElem.first > secondElem.first;

}

GraphCoordinateTransformer::GraphCoordinateTransformer(const backend::AbstractGraph& graph)
{

    uint64_t no_vertices = graph.getNoVertices();
    
    #ifdef _WIN32
        //initialize D to 0 matrix
        Eigen::MatrixXd D = Eigen::MatrixXd::Zero(no_vertices,no_vertices);

        // populate the matrix D
        for (auto& e : graph.getFullyConnected())
        {
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

        for (uint64_t i = 0; i < no_eigenvals; i++)
        {
            std::complex<double> C;
            C = es.eigenvalues().col(0)[i];
            ordered_evals.emplace_back(std::norm(C),i);
        }

        /* // --testing purposes --
        for(auto& el: ordered_evals){
            std::cout<<"norm: "<<el.first<<"; index: "<<el.second<<"\n";
        }*/

        // order eigenvalues in descending order
        std::sort(ordered_evals.begin(),ordered_evals.end(),pairCompare);

        Eigen::MatrixXcd V(no_vertices,dimensions);
        Eigen::MatrixXcd Diag = Eigen::MatrixXcd::Zero(dimensions,dimensions);
        for (unsigned int i = 0; i < dimensions; i++)
        {
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
        for (unsigned int i = 0; i < no_vertices; i++)
        {
            double coord_x = std::real(Y.row(i)[0]);
            double coord_y = std::real(Y.row(i)[1]);
            map_coord[i] = std::make_pair(coord_x,coord_y);
        }
    #else
        // initialize D to 0 matrix
        // less connectivity
        arma::mat D = arma::zeros<arma::mat>(no_vertices,no_vertices);
        //for(unsigned int i = 0; i < no_vertices; i++)
        //    for(unsigned int j = 0; j < no_vertices; j++)
        //        D(i,j) = 0;
        
        // populate the matrix D
        for(auto& e : graph.getFullyConnected()){
            D(e.first.first,e.first.second) = e.second;
            //std::cout<<"("<<e.first.first<<","<<e.first.second<<")";
            //std::cout<<"weight: "<<e.second<<"\n";
        }

        //centering matrix J
        arma::mat J = arma::mat(no_vertices,no_vertices);
        J = arma::eye<arma::mat>(no_vertices,no_vertices)
              - (1.0/no_vertices)*arma::ones<arma::mat>(no_vertices,no_vertices);

        // squared-distance matrix
        arma::mat S = arma::mat(no_vertices,no_vertices);
        // coefficient-wise multiplication and after the operation
        // converted back to matrix object
        S = D % D;

        //S.print("S = ");

        arma::sp_mat Z = arma::sp_mat(no_vertices,no_vertices);
        Z = -0.5 * J *S * J;
        uint64_t dimensions = 2; // for a 2D representation

        //Z.print("Z = ");

        arma::cx_vec eigval;
        arma::cx_mat eigvec;
        
        // getting the eigenvalues and eigenvectors by largest of magnitude
        arma::eigs_gen(eigval,eigvec,Z,dimensions,"lm");

        /* // --testing purposes --
        eigval.print("The eigenvalues are: ");
        eigvec.print("The eigenvectors are: ");
        */

        arma::cx_mat Diag = arma::zeros<arma::cx_mat>(dimensions,dimensions);
        for(unsigned int i = 0; i < dimensions; i++)
            Diag(i,i) = eigval(i);
        
        //Diag.print("The diagonal eigenvalue matrix is: ");

        arma::cx_mat Y = arma::cx_mat(no_vertices,dimensions);
        Y = eigvec*arma::sqrt(Diag);

        //Y.print("Y is: ");

        // next transform Y ---> map_coord
        for(unsigned int i = 0; i < no_vertices; i++){
            double coord_x = std::real(Y(i,0));
            double coord_y = std::real(Y(i,1));
            map_coord[i] = std::make_pair(coord_x,coord_y);
        }
    #endif    
}

std::map<backend::VertexId,std::pair<double,double>>
        GraphCoordinateTransformer::getNormalizedMap(uint64_t height, uint64_t width, uint64_t offset)
{
    if (map_coord.empty()) { return map_coord; }

    double min_x,max_x,min_y,max_y;
    min_x = max_x = (map_coord.begin()->second).first;
    min_y = max_y = (map_coord.begin()->second).second;
    for (auto& elem:map_coord)
    {
        if (elem.second.first > max_x) { max_x = elem.second.first; }
        if (elem.second.first < min_x) { min_x = elem.second.first; }
        if (elem.second.second > max_y) { max_y = elem.second.second; }
        if (elem.second.second < min_y) { min_y = elem.second.second; }
    }

    for (auto& elem:map_coord)
    {
        // x coordinate
        elem.second.first =
            (elem.second.first - min_x)*(width-2*offset)/(max_x - min_x)+offset;
        // y coordinate
        elem.second.second =
            (elem.second.second - min_y)*(height-2*offset)/(max_y - min_y) + offset;
    }

    return map_coord;
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