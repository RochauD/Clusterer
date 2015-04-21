#include "TestUniformCrossoverEngine.hpp"
#include "../include/UniformCrossoverEngine.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestUniformCrossoverEngine);

/**
 * @brief Sets up an encoding object with a sample graph
 */
void TestUniformCrossoverEngine::setUp(void)
{
    g= new Graph();
    Vertex v0(0);
    Vertex v1(1);
    Vertex v2(2);
    Vertex v3(3);

    g->addVertex(v0);
    g->addVertex(v1);
    g->addVertex(v2);
    g->addVertex(v3);

    rng = new std::mt19937();
    testObj = new UniformCrossoverEngine(rng);
}

/**
 * @brief Deletes the sample object
 */
void TestUniformCrossoverEngine::tearDown(void)
{
    delete g;
    delete testObj;
}

/**
 * @brief Test if getting random solution works
 */
void TestUniformCrossoverEngine::testCrossover(void)
{
    IntegerVectorEncoding p1(g);
    IntegerVectorEncoding p2(g);
    IntegerVectorEncoding child(g);

    // Initialize first parent
    p1.addToCluster(0, 0);
    p1.addToCluster(1, 1);
    p1.addToCluster(2, 2);
    p1.addToCluster(3, 3);
    // Initialize second parent
    p2.addToCluster(0, 4);
    p2.addToCluster(1, 5);
    p2.addToCluster(2, 6);
    p2.addToCluster(3, 7);

    for (int i = 0; i < 10; i++)
    {
        testObj->crossover(p1, p2, child);

        CPPUNIT_ASSERT(4 == child.getEncoding().size());
        CPPUNIT_ASSERT(4 >= child.getClusterCount());
        
        // Assert all clusters come either from one or the other parent
        for (int j = 0; j < 4; j++)
        {
            bool oneOrTheOther =
                ((child.getClusterOfVertex(j) == p1.getClusterOfVertex(j)) || 
                (child.getClusterOfVertex(j) == p2.getClusterOfVertex(j)));

            CPPUNIT_ASSERT(oneOrTheOther);
        }
    }
}

