#include "TestGraphCoordinateTransformer.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestGraphCoordinateTransformer);

void TestGraphCoordinateTransformer::setUp(void)
{

}

void TestGraphCoordinateTransformer::tearDown(void)
{

}

void TestGraphCoordinateTransformer::printSol(const ClusterEncoding& clusterSol)
{
    for(unsigned int i = 0; i < clusterSol.size(); i++){
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
}

void TestGraphCoordinateTransformer::testObtainedCoordinates(void)
{
    CPPUNIT_ASSERT(false);
}