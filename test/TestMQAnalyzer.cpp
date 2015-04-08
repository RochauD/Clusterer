#include "TestMQAnalyzer.hpp"

#include <limits>

CPPUNIT_TEST_SUITE_REGISTRATION(TestMQAnalyzer);

void TestMQAnalyzer::setUp(void)
{

}

void TestMQAnalyzer::tearDown(void)
{

}

void TestMQAnalyzer::testAnalyzeSingleElementClustersOnly(void)
{
    clb::Graph graph;

    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));

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

    clb::IntegerVectorEncoding solution(graph);

    solution.addToCluster(0, 0);
    solution.addToCluster(1, 1);
    solution.addToCluster(2, 2);
    solution.addToCluster(3, 3);

    double result = this->mqAnalyzer.analyze(solution, graph);
    double actualValue = 0.0; // @todo check with hand calculated one!!!
    CPPUNIT_ASSERT((result <  actualValue + std::numeric_limits<double>::epsilon()) &&
                   (result > -actualValue - std::numeric_limits<double>::epsilon()));
}

void TestMQAnalyzer::testAnalyzeOneClusterOnly(void)
{
    clb::Graph graph;

    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));

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

    clb::IntegerVectorEncoding solution(graph);

    solution.addToCluster(0, 0);
    solution.addToCluster(1, 0);
    solution.addToCluster(2, 0);
    solution.addToCluster(3, 0);

    double result = this->mqAnalyzer.analyze(solution, graph);
    double actualValue = 0.0; // @todo check with hand calculated one!!!
    CPPUNIT_ASSERT((result <  actualValue + std::numeric_limits<double>::epsilon()) &&
                   (result > -actualValue - std::numeric_limits<double>::epsilon()));
}

void TestMQAnalyzer::testAnalyzeFullyConnectedGraphTwoClusters(void)
{
    clb::Graph graph;

    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));

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

    clb::IntegerVectorEncoding solution(graph);

    solution.addToCluster(0, 0);
    solution.addToCluster(1, 0);
    solution.addToCluster(2, 1);
    solution.addToCluster(3, 1);

    double result = this->mqAnalyzer.analyze(solution, graph);
    double actualValue = 0.0; // @todo check with hand calculated one!!!
    CPPUNIT_ASSERT((result <  actualValue + std::numeric_limits<double>::epsilon()) &&
                   (result > -actualValue - std::numeric_limits<double>::epsilon()));
}
