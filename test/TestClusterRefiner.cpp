#include "TestClusterRefiner.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestClusterRefiner);

void TestClusterRefiner::setUp(void)
{

}

void TestClusterRefiner::tearDown(void)
{

}

void TestClusterRefiner::printSol(const ClusterEncoding& clusterSol,int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
}

void TestClusterRefiner::testRefineFunction(void)
{
    clb::Graph graph;

    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));

    graph.addEdge(Vertex(0), Vertex(1), 0.125);
    graph.addEdge(Vertex(0), Vertex(2), 0.125);
    graph.addEdge(Vertex(0), Vertex(3), 0.125);

    graph.addEdge(Vertex(1), Vertex(0), 0.25);
    graph.addEdge(Vertex(1), Vertex(2), 0.25);
    graph.addEdge(Vertex(1), Vertex(3), 0.25);

    graph.addEdge(Vertex(2), Vertex(0), 0.5);
    graph.addEdge(Vertex(2), Vertex(1), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.5);

    graph.addEdge(Vertex(3), Vertex(0), 0.75);

    graph.addEdge(Vertex(4), Vertex(0), 0.5);
    graph.addEdge(Vertex(4), Vertex(1), 0.5);

    clb::ClusterRefiner refiner(&mt,0.5);

    clb::IntegerVectorEncoding solution(&graph);

    solution.addToCluster(0,0);
    solution.addToCluster(1,2);
    solution.addToCluster(2,2);
    solution.addToCluster(3,1);
    solution.addToCluster(4,3);

    clb::IntegerVectorEncoding result1 = solution;
    refiner.refine(result1,graph);
    double o1 = refiner.getOriginalClusterRefineDensity();
    double a1 = refiner.getAfterClusterRefineDensity();

    clb::IntegerVectorEncoding result2 = solution;
    refiner.refine(result2,graph);
    double o2 = refiner.getOriginalClusterRefineDensity();
    double a2 = refiner.getAfterClusterRefineDensity();

    clb::IntegerVectorEncoding result3 = solution;
    refiner.refine(result3,graph);
    double o3 = refiner.getOriginalClusterRefineDensity();
    double a3 = refiner.getAfterClusterRefineDensity();

    clb::IntegerVectorEncoding result4 = solution;
    refiner.refine(result4,graph);
    double o4 = refiner.getOriginalClusterRefineDensity();
    double a4 = refiner.getAfterClusterRefineDensity();

    clb::IntegerVectorEncoding result5 = solution;
    refiner.refine(result5,graph);
    double o5 = refiner.getOriginalClusterRefineDensity();
    double a5 = refiner.getAfterClusterRefineDensity();

    //int checker1,checker2,checker3,checker4,checker5;
    //checker1 = checker2 = checker3 = checker4 = checker5 = 0;

    CPPUNIT_ASSERT(a1 >= o1 && a2 >= o2 && a3 >= o3 && a4 >= o4 && a5 >= o5);
}
