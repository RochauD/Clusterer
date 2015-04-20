#include "TestExplorationMutation.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestExplorationMutation);

void TestExplorationMutation::setUp(void)
{

}

void TestExplorationMutation::tearDown(void)
{

}

void TestExplorationMutation::printSol(const ClusterEncoding& clusterSol,int n){
    for(int i = 0; i < n; i++){
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
}

void TestExplorationMutation::testMutateFunction(void){

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

    clb::IntegerVectorEncoding solution(&graph);

    solution.addToCluster(0,0);
    solution.addToCluster(1,2);
    solution.addToCluster(2,2);
    solution.addToCluster(3,1);
    solution.addToCluster(4,3);
    
    clb::IntegerVectorEncoding result1 = solution;
    this->mutator.mutate(result1);

    clb::IntegerVectorEncoding result2 = solution;
    this->mutator.mutate(result2);

    clb::IntegerVectorEncoding result3 = solution;
    this->mutator.mutate(result3);

    clb::IntegerVectorEncoding result4 = solution;
    this->mutator.mutate(result4);

    clb::IntegerVectorEncoding result5 = solution;
    this->mutator.mutate(result5);

    int checker1,checker2,checker3,checker4,checker5;
    checker1 = checker2 = checker3 = checker4 = checker5 = 0;
    
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

    for(int i = 0; i < 5; i++){
    	if(solution.getClusterOfVertex(i) != result1.getClusterOfVertex(i)) checker1++;
    	if(solution.getClusterOfVertex(i) != result2.getClusterOfVertex(i)) checker2++;
    	if(solution.getClusterOfVertex(i) != result3.getClusterOfVertex(i)) checker3++;
    	if(solution.getClusterOfVertex(i) != result4.getClusterOfVertex(i)) checker4++;
    	if(solution.getClusterOfVertex(i) != result5.getClusterOfVertex(i)) checker5++;
    }

    std::cout<<"checker1: "<<checker1<<"\n";
    std::cout<<"checker2: "<<checker2<<"\n";
    std::cout<<"checker3: "<<checker3<<"\n";
    std::cout<<"checker4: "<<checker4<<"\n";
    std::cout<<"checker5: "<<checker5<<"\n";

    CPPUNIT_ASSERT(checker1 <= 1 && checker2 <= 1 && checker3 == 1
    	&& checker4 <= 1 && checker5 <= 1);

}