#include "TestIntegerEncodingInitializer.hpp"
#include "../include/IntegerEncodingInitializer.hpp"
#include "../include/Graph.hpp"
#include "../include/Vertex.hpp"
#include "../include/IntegerVectorEncoding.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestIntegerEncodingInitializer);

/**
 * @brief Sets up an encoding object with a sample graph
 */
void TestIntegerEncodingInitializer::setUp(void)
{
    g = new Graph();
    Vertex v0(0);
    Vertex v1(1);
    Vertex v2(2);
    Vertex v3(3);

    g->addVertex(v0);
    g->addVertex(v1);
    g->addVertex(v2);
    g->addVertex(v3);

    testObj1 = new IntegerEncodingInitializer(g, 3);
    testObj2 = new IntegerEncodingInitializer(g);
}

/**
 * @brief Deletes the sample object
 */
void TestIntegerEncodingInitializer::tearDown(void)
{
    delete testObj1;
    delete testObj2;
    delete g;
}

/**
 * @brief Test if getting random solution works
 */
void TestIntegerEncodingInitializer::testGetRandomSolution(void)
{
    IntegerVectorEncoding solution1 = testObj1->getRandomSolution();
    CPPUNIT_ASSERT(3 >= solution1.getClusterCount());

    IntegerVectorEncoding solution2 = testObj2->getRandomSolution();
    CPPUNIT_ASSERT(g->getNoVertices() >= solution2.getClusterCount());

    for (int v = 0; v < g->getNoVertices(); v++)
    {
        CPPUNIT_ASSERT(solution1.getClusterOfVertex(v) >= 0);
        CPPUNIT_ASSERT(solution1.getClusterOfVertex(v) < 3);

        CPPUNIT_ASSERT(solution2.getClusterOfVertex(v) >= 0);
        CPPUNIT_ASSERT(solution2.getClusterOfVertex(v) < g->getNoVertices());

    }


}
