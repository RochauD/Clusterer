#include "TestClusterRefiner.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestClusterRefiner);

void TestClusterRefiner::setUp(void)
{

}

void TestClusterRefiner::tearDown(void)
{

}

void TestClusterRefiner::printSol(const ClusterEncoding& clusterSol,int n){
    for(int i = 0; i < n; i++){
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
}

void TestClusterRefiner::testRefineFunction(void){
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
    graph.addEdge(Vertex(3), Vertex(1), 0.75);
    graph.addEdge(Vertex(3), Vertex(2), 0.75);

    graph.addEdge(Vertex(4), Vertex(0), 0.55);
    graph.addEdge(Vertex(4), Vertex(1), 0.55);

    clb::ClusterRefiner mutator(&mt,0.5);

    clb::IntegerVectorEncoding solution(&graph);

    solution.addToCluster(0,0);
    solution.addToCluster(1,2);
    solution.addToCluster(2,2);
    solution.addToCluster(3,1);
    solution.addToCluster(4,3);
    
    std::cout<<"before mutate--test\n";
    clb::IntegerVectorEncoding result1 = solution;
    mutator.refine(result1,graph);

    clb::IntegerVectorEncoding result2 = solution;
    mutator.refine(result2,graph);

    clb::IntegerVectorEncoding result3 = solution;
    mutator.refine(result3,graph);

    clb::IntegerVectorEncoding result4 = solution;
    mutator.refine(result4,graph);

    clb::IntegerVectorEncoding result5 = solution;
    mutator.refine(result5,graph);

    //int checker1,checker2,checker3,checker4,checker5;
    //checker1 = checker2 = checker3 = checker4 = checker5 = 0;
    
    std::cout<<"\noriginal: ";
    printSol(solution,5);

    std::cout<<"mutated: ";
    printSol(result1,5);

    std::cout<<"mutated: ";
    printSol(result2,5);

    std::cout<<"mutated: ";
    printSol(result3,5);

    std::cout<<"mutated: ";
    printSol(result4,5);

    std::cout<<"mutated: ";
    printSol(result5,5);

    /*
    for(int i = 0; i < 5; i++){
    	if(solution.getClusterOfVertex(i) != result1.getClusterOfVertex(i)) checker1++;
    	if(solution.getClusterOfVertex(i) != result2.getClusterOfVertex(i)) checker2++;
    	if(solution.getClusterOfVertex(i) != result3.getClusterOfVertex(i)) checker3++;
    	if(solution.getClusterOfVertex(i) != result4.getClusterOfVertex(i)) checker4++;
    	if(solution.getClusterOfVertex(i) != result5.getClusterOfVertex(i)) checker5++;
    }*/
    //int solClusterCount = solution.getClusterCount();
    //int result1CC = result1.getClusterCount();
    //int result2CC = result2.getClusterCount();
    //int result3CC = result3.getClusterCount();
    //int result4CC = result4.getClusterCount();
    //int result5CC = result5.getClusterCount();


    /*
    std::cout<<"checker1: "<<checker1<<"\n";
    std::cout<<"checker2: "<<checker2<<"\n";
    std::cout<<"checker3: "<<checker3<<"\n";
    std::cout<<"checker4: "<<checker4<<"\n";
    std::cout<<"checker5: "<<checker5<<"\n";*/


    //CPPUNIT_ASSERT(std::abs(solClusterCount-result1CC) <= 2 &&
      //  std::abs(solClusterCount-result2CC) <= 2 &&
        //std::abs(solClusterCount-result3CC) <= 2 &&
        //std::abs(solClusterCount-result4CC) <= 2 &&
        //std::abs(solClusterCount-result5CC) <= 2);
    
}
