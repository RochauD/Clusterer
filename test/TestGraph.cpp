#include "TestGraph.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestGraph);

void TestGraph::setUp(void)
{

}

void TestGraph::tearDown(void)
{

}

void TestGraph::testGetNoVerticesReturnsZeroOnEmptyGraph(void)
{
    Graph g;
    CPPUNIT_ASSERT(g.getNoVertices() == 0);
}

void TestGraph::testGetNoVerticesWorks(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    CPPUNIT_ASSERT(g.getNoVertices() == 2);
}

void TestGraph::testGetNoEdgesReturnsZeroOnEmptyGraph(void)
{
    Graph g;
    CPPUNIT_ASSERT(g.getNoEdges() == 0);
}

void TestGraph::testGetNoEdgesWorks(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1));
    g.addEdge(Vertex(1), Vertex(0));
    CPPUNIT_ASSERT(g.getNoEdges() == 2);
}

void TestGraph::testAddVertex(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    auto vec = g.getVertices();
    CPPUNIT_ASSERT(vec[0] == 0);
}

void TestGraph::testAddEdgeWithoutWeight(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1));
    auto vec = g.getEdges();
    CPPUNIT_ASSERT(vec[0].first == 0);
    CPPUNIT_ASSERT(vec[0].second == 1);
}

void TestGraph::testAddEdgeWithWeight(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1), 1.5);
    auto vec = g.getEdgesAndWeights();
    CPPUNIT_ASSERT(vec[0].first.first == 0);
    CPPUNIT_ASSERT(vec[0].first.second == 1);
    CPPUNIT_ASSERT(vec[0].second == 1.5);
}

void TestGraph::testSetEdgeWeight(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1), 1.5);
    auto vec = g.getEdgesAndWeights();
    CPPUNIT_ASSERT(vec[0].first.first == 0);
    CPPUNIT_ASSERT(vec[0].first.second == 1);
    CPPUNIT_ASSERT(vec[0].second == 1.5);
    g.setEdgeWeight(Vertex(0), Vertex(1), 2.5);
    vec = g.getEdgesAndWeights();
    CPPUNIT_ASSERT(vec[0].first.first == 0);
    CPPUNIT_ASSERT(vec[0].first.second == 1);
    CPPUNIT_ASSERT(vec[0].second == 2.5);
}

void TestGraph::testGetEdgeWeight(void)
{
    double result = 0.0;
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1), 1.5);
    CPPUNIT_ASSERT(g.getEdgeWeight(Vertex(0), Vertex(1), &result) == true);
    CPPUNIT_ASSERT(result == 1.5);
}

void TestGraph::testGetEdgeWeightNonExistentEdge(void)
{
    double result = 0.0;
    Graph g;
    CPPUNIT_ASSERT(g.getEdgeWeight(Vertex(0), Vertex(1), &result) == false);
}

void TestGraph::testGetVertices(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addVertex(Vertex(2));
    auto vec = g.getVertices();
    CPPUNIT_ASSERT(vec[0] == 0);
    CPPUNIT_ASSERT(vec[1] == 1);
    CPPUNIT_ASSERT(vec[2] == 2);
}

void TestGraph::testGetVerticesOnEmptyGraph(void)
{
    Graph g;
    auto vec = g.getVertices();
    CPPUNIT_ASSERT(vec.empty() == true);
}

void TestGraph::testGetEdges(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1));
    g.addEdge(Vertex(1), Vertex(0));
    auto vec = g.getEdges();
    CPPUNIT_ASSERT(vec[0] == std::make_pair(VertexId(0), VertexId(1)));
    CPPUNIT_ASSERT(vec[1] == std::make_pair(VertexId(1), VertexId(0)));
}

void TestGraph::testGetEdgesOnEmptyGraph(void)
{
    Graph g;
    auto vec = g.getEdges();
    CPPUNIT_ASSERT(vec.empty() == true);
}

void TestGraph::testGetEdgesAndWeights(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1), 1.0);
    g.addEdge(Vertex(1), Vertex(0), 2.5);
    auto vec = g.getEdgesAndWeights();
    CPPUNIT_ASSERT(vec[0].first == std::make_pair(VertexId(0), VertexId(1)));
    CPPUNIT_ASSERT(vec[0].second == 1.0);
    CPPUNIT_ASSERT(vec[1].first == std::make_pair(VertexId(1), VertexId(0)));
    CPPUNIT_ASSERT(vec[1].second == 2.5);
}

void TestGraph::testGetEdgesAndWeightsOnEmptyGraph(void)
{
    Graph g;
    auto vec = g.getEdgesAndWeights();
    CPPUNIT_ASSERT(vec.empty() == true);
}

void TestGraph::testGetNeighbors(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1), 1.0);
    auto vec = g.getNeighbors(Vertex(0));
    CPPUNIT_ASSERT(vec[0] == VertexId(1));
}

void TestGraph::testGetNeighborsOnThreeNodeGraph(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addVertex(Vertex(2));
    g.addEdge(Vertex(0), Vertex(1), 1.0);
    g.addEdge(Vertex(0), Vertex(2), 1.0);
    auto vec = g.getNeighbors(Vertex(0));
    CPPUNIT_ASSERT(vec[0] == VertexId(1));
    CPPUNIT_ASSERT(vec[1] == VertexId(2));
}

void TestGraph::testGetNeighborsOnEmptyGraph(void)
{
    Graph g;
    auto vec = g.getNeighbors(Vertex(0));
    CPPUNIT_ASSERT(vec.empty() == true);
}

void TestGraph::testExistsEdge(void)
{
    Graph g;
    g.addVertex(Vertex(0));
    g.addVertex(Vertex(1));
    g.addEdge(Vertex(0), Vertex(1), 1.0);
    CPPUNIT_ASSERT(true == g.existsEdge(Vertex(0), Vertex(1)));
}

void TestGraph::testExistsEdgeOnEmptyGraph(void)
{
    Graph g;
    CPPUNIT_ASSERT(false == g.existsEdge(Vertex(0), Vertex(1)));
}
