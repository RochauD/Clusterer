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
    std::vector<PopulationMember<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        PopulationMember<IntegerVectorEncoding, double> member;
        member.fitnessValue = 0.0;
        member.modified = true;
        member.populationEncoding = initVec.getRandomSolution();
        vecPop.push_back(member);
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<PopulationMember<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 1);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.populationEncoding, &graph) == e.fitnessValue);
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
    std::vector<PopulationMember<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        PopulationMember<IntegerVectorEncoding, double> member;
        member.fitnessValue = 0.0;
        member.modified = true;
        member.populationEncoding = initVec.getRandomSolution();
        vecPop.push_back(member);
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<PopulationMember<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 2);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.populationEncoding, &graph) == e.fitnessValue);
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
    std::vector<PopulationMember<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        PopulationMember<IntegerVectorEncoding, double> member;
        member.fitnessValue = 0.0;
        member.modified = true;
        member.populationEncoding = initVec.getRandomSolution();
        vecPop.push_back(member);
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<PopulationMember<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 3);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.populationEncoding, &graph) == e.fitnessValue);
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
    std::vector<PopulationMember<IntegerVectorEncoding, double>> vecPop;
    for (size_t i = 0; i < populationSize; i++)
    {
        PopulationMember<IntegerVectorEncoding, double> member;
        member.fitnessValue = 0.0;
        member.modified = true;
        member.populationEncoding = initVec.getRandomSolution();
        vecPop.push_back(member);
    }

    ClusteringPopulationAnalyzer<FitnessAnalyzer, std::vector<PopulationMember<IntegerVectorEncoding, double>>> analyzer(&graph, &vecPop, 4);
    analyzer.evaluatePopulation();
    FitnessAnalyzer singleAnalyzer;
    for (auto& e : vecPop)
    {
        CPPUNIT_ASSERT(singleAnalyzer.analyze(&e.populationEncoding, &graph) == e.fitnessValue);
    }
}
