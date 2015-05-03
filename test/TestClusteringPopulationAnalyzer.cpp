#include "TestClusteringPopulationAnalyzer.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestClusteringPopulationAnalyzer);

size_t populationSize = 1000;

void TestClusteringPopulationAnalyzer::setUp(void)
{

}

void TestClusteringPopulationAnalyzer::tearDown(void)
{

}

void TestClusteringPopulationAnalyzer::testEvaluatePopulationOneThread(void)
{
    Graph graph;
    // Initialize graph
    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));
    graph.addVertex(Vertex(5));
    graph.addVertex(Vertex(6));
    graph.addVertex(Vertex(7));

    graph.addEdge(Vertex(0), Vertex(1), 0.2);
    graph.addEdge(Vertex(1), Vertex(2), 0.3);
    graph.addEdge(Vertex(1), Vertex(3), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.4);
    graph.addEdge(Vertex(3), Vertex(4), 0.2);
    graph.addEdge(Vertex(4), Vertex(5), 0.5);
    graph.addEdge(Vertex(4), Vertex(6), 0.6);
    graph.addEdge(Vertex(5), Vertex(6), 0.7);
    graph.addEdge(Vertex(6), Vertex(7), 0.1);

    IntegerEncodingInitializer initVec(&graph);
    std::vector<std::pair<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        vecPop.push_back(std::make_pair(initVec.getRandomSolution(), 1.0));
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<std::pair<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 1);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.first, &graph) == e.second);
    }
}

void TestClusteringPopulationAnalyzer::testEvaluatePopulationTwoThreads(void)
{
    Graph graph;
    // Initialize graph
    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));
    graph.addVertex(Vertex(5));
    graph.addVertex(Vertex(6));
    graph.addVertex(Vertex(7));

    graph.addEdge(Vertex(0), Vertex(1), 0.2);
    graph.addEdge(Vertex(1), Vertex(2), 0.3);
    graph.addEdge(Vertex(1), Vertex(3), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.4);
    graph.addEdge(Vertex(3), Vertex(4), 0.2);
    graph.addEdge(Vertex(4), Vertex(5), 0.5);
    graph.addEdge(Vertex(4), Vertex(6), 0.6);
    graph.addEdge(Vertex(5), Vertex(6), 0.7);
    graph.addEdge(Vertex(6), Vertex(7), 0.1);

    IntegerEncodingInitializer initVec(&graph);
    std::vector<std::pair<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        vecPop.push_back(std::make_pair(initVec.getRandomSolution(), 1.0));
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<std::pair<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 2);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.first, &graph) == e.second);
    }
}

void TestClusteringPopulationAnalyzer::testEvaluatePopulationThreeThreads(void)
{
    Graph graph;
    // Initialize graph
    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));
    graph.addVertex(Vertex(5));
    graph.addVertex(Vertex(6));
    graph.addVertex(Vertex(7));

    graph.addEdge(Vertex(0), Vertex(1), 0.2);
    graph.addEdge(Vertex(1), Vertex(2), 0.3);
    graph.addEdge(Vertex(1), Vertex(3), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.4);
    graph.addEdge(Vertex(3), Vertex(4), 0.2);
    graph.addEdge(Vertex(4), Vertex(5), 0.5);
    graph.addEdge(Vertex(4), Vertex(6), 0.6);
    graph.addEdge(Vertex(5), Vertex(6), 0.7);
    graph.addEdge(Vertex(6), Vertex(7), 0.1);

    IntegerEncodingInitializer initVec(&graph);
    std::vector<std::pair<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        vecPop.push_back(std::make_pair(initVec.getRandomSolution(), 1.0));
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<std::pair<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 3);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.first, &graph) == e.second);
    }
}

void TestClusteringPopulationAnalyzer::testEvaluatePopulationFourThreads(void)
{
    Graph graph;
    // Initialize graph
    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));
    graph.addVertex(Vertex(5));
    graph.addVertex(Vertex(6));
    graph.addVertex(Vertex(7));

    graph.addEdge(Vertex(0), Vertex(1), 0.2);
    graph.addEdge(Vertex(1), Vertex(2), 0.3);
    graph.addEdge(Vertex(1), Vertex(3), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.4);
    graph.addEdge(Vertex(3), Vertex(4), 0.2);
    graph.addEdge(Vertex(4), Vertex(5), 0.5);
    graph.addEdge(Vertex(4), Vertex(6), 0.6);
    graph.addEdge(Vertex(5), Vertex(6), 0.7);
    graph.addEdge(Vertex(6), Vertex(7), 0.1);

    IntegerEncodingInitializer initVec(&graph);
    std::vector<std::pair<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        vecPop.push_back(std::make_pair(initVec.getRandomSolution(), 1.0));
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<std::pair<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 4);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.first, &graph) == e.second);
    }
}
