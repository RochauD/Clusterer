#include "TestFitnessAnalyzer.hpp"

#include <limits>

CPPUNIT_TEST_SUITE_REGISTRATION(TestFitnessAnalyzer);

// use double epsilon value
double testEpsilon = 2 * std::numeric_limits<double>::epsilon();

void TestFitnessAnalyzer::setUp(void)
{
    // Initialize graph 1
    graph1.addVertex(Vertex(0));
    graph1.addVertex(Vertex(1));
    graph1.addVertex(Vertex(2));
    graph1.addVertex(Vertex(3));
    graph1.addVertex(Vertex(4));

    graph1.addEdge(Vertex(0), Vertex(1), 0.2);
    graph1.addEdge(Vertex(0), Vertex(2), 0.1);
    graph1.addEdge(Vertex(1), Vertex(2), 0.3);
    graph1.addEdge(Vertex(3), Vertex(4), 0.4);

    // Initialize graph 2
    graph2.addVertex(Vertex(0));
    graph2.addVertex(Vertex(1));
    graph2.addVertex(Vertex(2));
    graph2.addVertex(Vertex(3));
    graph2.addVertex(Vertex(4));
    graph2.addVertex(Vertex(5));
    graph2.addVertex(Vertex(6));
    graph2.addVertex(Vertex(7));

    graph2.addEdge(Vertex(0), Vertex(1), 0.2);
    graph2.addEdge(Vertex(1), Vertex(2), 0.3);
    graph2.addEdge(Vertex(1), Vertex(3), 0.5);
    graph2.addEdge(Vertex(2), Vertex(3), 0.4);
    graph2.addEdge(Vertex(3), Vertex(4), 0.2);
    graph2.addEdge(Vertex(4), Vertex(5), 0.5);
    graph2.addEdge(Vertex(4), Vertex(6), 0.6);
    graph2.addEdge(Vertex(5), Vertex(6), 0.7);
    graph2.addEdge(Vertex(6), Vertex(7), 0.1);

}

void TestFitnessAnalyzer::tearDown(void)
{

}

void TestFitnessAnalyzer::testAnalyzeSingleElementClustersOnly(void)
{
    // Test for graph1
    // clustering solution for graph1
    clb::IntegerVectorEncoding solution1(&graph1);

    solution1.addToCluster(0, 0);
    solution1.addToCluster(1, 1);
    solution1.addToCluster(2, 2);
    solution1.addToCluster(3, 3);
    solution1.addToCluster(4, 4);

    double result = this->fitnessAnalyzer.analyze(&solution1, &graph1);
    double actualValue = 11.0/8.0;
    CPPUNIT_ASSERT((result < actualValue + testEpsilon) &&
                   (result > actualValue - testEpsilon));

    // Test for graph2
    // clustering solution for graph2
    clb::IntegerVectorEncoding solution2(&graph2);

    solution2.addToCluster(0, 0);
    solution2.addToCluster(1, 1);
    solution2.addToCluster(2, 2);
    solution2.addToCluster(3, 3);
    solution2.addToCluster(4, 4);
    solution2.addToCluster(5, 5);
    solution2.addToCluster(6, 6);
    solution2.addToCluster(7, 7);

    result = this->fitnessAnalyzer.analyze(&solution2, &graph2);
    actualValue = 43.0/32.0;
    CPPUNIT_ASSERT((result < actualValue + testEpsilon) &&
                   (result > actualValue - testEpsilon));
}

void TestFitnessAnalyzer::testAnalyzeOneClusterOnly(void)
{
    // Test for graph1
    // clustering solution for graph1
    clb::IntegerVectorEncoding solution1(&graph1);

    solution1.addToCluster(0, 0);
    solution1.addToCluster(1, 0);
    solution1.addToCluster(2, 0);
    solution1.addToCluster(3, 0);
    solution1.addToCluster(4, 0);

    double result = this->fitnessAnalyzer.analyze(&solution1, &graph1);
    double actualValue = 31.0/50.0;
    CPPUNIT_ASSERT((result < actualValue + testEpsilon) &&
                   (result > actualValue - testEpsilon));

    // Test for graph2
    // clustering solution for graph2
    clb::IntegerVectorEncoding solution2(&graph2);

    solution2.addToCluster(0, 0);
    solution2.addToCluster(1, 0);
    solution2.addToCluster(2, 0);
    solution2.addToCluster(3, 0);
    solution2.addToCluster(4, 0);
    solution2.addToCluster(5, 0);
    solution2.addToCluster(6, 0);
    solution2.addToCluster(7, 0);

    result = this->fitnessAnalyzer.analyze(&solution2, &graph2);
    actualValue = 167.0/256.0;
    CPPUNIT_ASSERT((result < actualValue + testEpsilon) &&
                   (result > actualValue - testEpsilon));
}

void TestFitnessAnalyzer::testAnalyzeTwoClusters(void)
{
    // Test for graph1
    // clustering solution for graph1
    clb::IntegerVectorEncoding solution1(&graph1);

    solution1.addToCluster(0, 0);
    solution1.addToCluster(1, 0);
    solution1.addToCluster(2, 0);
    solution1.addToCluster(3, 1);
    solution1.addToCluster(4, 1);

    double result = this->fitnessAnalyzer.analyze(&solution1, &graph1);
    double actualValue = 149.0/120.0;
    CPPUNIT_ASSERT((result < actualValue + testEpsilon) &&
                   (result > actualValue - testEpsilon));

    // Test for graph2
    // clustering solution for graph2
    clb::IntegerVectorEncoding solution2(&graph2);

    solution2.addToCluster(0, 0);
    solution2.addToCluster(1, 0);
    solution2.addToCluster(2, 0);
    solution2.addToCluster(3, 0);
    solution2.addToCluster(4, 1);
    solution2.addToCluster(5, 1);
    solution2.addToCluster(6, 1);
    solution2.addToCluster(7, 1);

    result = this->fitnessAnalyzer.analyze(&solution2, &graph2);
    actualValue = 5513.0/4480.0;
    CPPUNIT_ASSERT((result < actualValue + testEpsilon) &&
                   (result > actualValue - testEpsilon));
}
