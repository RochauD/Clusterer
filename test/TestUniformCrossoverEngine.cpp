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
    g1= new Graph();
    Vertex v0(0);
    Vertex v1(1);
    Vertex v2(2);
    Vertex v3(3);

    g1->addVertex(v0);
    g1->addVertex(v1);
    g1->addVertex(v2);
    g1->addVertex(v3);

    g2= new Graph();
    Vertex v4(5);
    Vertex v5(6);
    Vertex v6(7);
    Vertex v7(8);

    g2->addVertex(v4);
    g2->addVertex(v5);
    g2->addVertex(v6);
    g2->addVertex(v7);

    rng = new std::mt19937();
    testObj = new UniformCrossoverEngine(rng);
}

/**
 * @brief Deletes the sample object
 */
void TestUniformCrossoverEngine::tearDown(void)
{
    delete g1;
    delete g2;
    delete testObj;
}

/**
 * @brief Test if getting random solution works
 */
void TestUniformCrossoverEngine::testCrossover(void)
{

    IntegerVectorEncoding p1(g1);
    IntegerVectorEncoding p2(g2);
    IntegerVectorEncoding child(g1);

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

