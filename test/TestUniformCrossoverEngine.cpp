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
    g2->addVertex(v4);
    g2->addVertex(v5);
    g2->addVertex(v6);


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
    delete rng;
    delete testObj;
}

/**
 * @brief Check if two clusters are the same as expected clusters
 */
bool compareClusters(IntegerVectorEncoding c, 
                     IntegerVectorEncoding e)
{
    if (c.size() != e.size())
    { 
        return false; 
    }

    for (uint64_t i = 0; i < c.size(); i++)
    {
        if (c.getClusterOfVertex(i) != e.getClusterOfVertex(i))
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Test if getting random solution works
 */
void TestUniformCrossoverEngine::testCrossover(void)
{

    IntegerVectorEncoding p1(g1);
    IntegerVectorEncoding p2(g1);
    IntegerVectorEncoding p3(g2);
    IntegerVectorEncoding p4(g2);
    IntegerVectorEncoding child(g1);
    IntegerVectorEncoding child2(g2);

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

    // Initialize third parent
    p3.addToCluster(0, 0);
    p3.addToCluster(1, 0);
    p3.addToCluster(2, 1);

    // Initialize fourth parent
    p4.addToCluster(0, 2);
    p4.addToCluster(1, 1);
    p4.addToCluster(2, 0);

    // Declaring possible cases;
    IntegerVectorEncoding case1(g2), case2(g2), case3(g2), case4(g2);
    IntegerVectorEncoding case5(g2), case6(g2), case7(g2), case8(g2);

    bool found1, found2, found3, found4, found5, found6, found7, found8, foundOther;
    found1 = found2 = found3 = found4 = found5 = found6 =found7 = found8 = foundOther = false;

    // Defining cases
    case1.addToCluster(0,0);
    case1.addToCluster(1,0);
    case1.addToCluster(2,1);

    case2.addToCluster(0,0);
    case2.addToCluster(1,0);
    case2.addToCluster(2,0);

    case3.addToCluster(0,0);
    case3.addToCluster(1,1);
    case3.addToCluster(2,1);

    case4.addToCluster(0,0);
    case4.addToCluster(1,1);
    case4.addToCluster(2,0);

    case5.addToCluster(0,0);
    case5.addToCluster(1,1);
    case5.addToCluster(2,2);


    for (int i = 0; i < 1000; i++)
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


        testObj->crossover(p3, p4, child2);

        if (compareClusters(child2, case1))
        {
            found1 = true;
        } 
        else if (compareClusters(child2, case2))
        {
            found2 = true;
        }
        else if (compareClusters(child2, case3))
        {
            found3 = true;
        }
        else if (compareClusters(child2, case4))
        {
            found4 = true;
        }
        else if (compareClusters(child2, case5))
        {
            found5 = true;
        }
        else
        {
            foundOther = true;
        }
    } 

    CPPUNIT_ASSERT(found1);
    CPPUNIT_ASSERT(found2);
    CPPUNIT_ASSERT(found3);
    CPPUNIT_ASSERT(found4);
    CPPUNIT_ASSERT(found5);
    CPPUNIT_ASSERT(!foundOther);
}

