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

GraphCoordinateTransformer::GraphCoordinateTransformer(const backend::AbstractGraph& graph)
{
    // nothing for now
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