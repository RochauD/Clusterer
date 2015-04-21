#include "TestClusterwiseCrossoverEngine.hpp"
#include "../include/ClusterwiseCrossoverEngine.hpp"
#include "../include/IntegerVectorEncoding.hpp"
CPPUNIT_TEST_SUITE_REGISTRATION(TestClusterwiseCrossoverEngine);

/**
 * @brief Sets up an encoding object with a sample graph
 */
void TestClusterwiseCrossoverEngine::setUp(void)
{
    g= new Graph();
    Vertex v0(0);
    Vertex v1(1);
    Vertex v2(2);
    Vertex v3(3);
    Vertex v4(4);
    Vertex v5(5);

    g->addVertex(v0);
    g->addVertex(v1);
    g->addVertex(v2);
    g->addVertex(v3);
    g->addVertex(v4);
    g->addVertex(v5);

    rng = new std::mt19937();
    testObj = new ClusterwiseCrossoverEngine(rng);
}

/**
 * @brief Deletes the sample object
 */
void TestClusterwiseCrossoverEngine::tearDown(void)
{
    delete g;
    delete rng;
    delete testObj;
}

/**
 * @brief Check if two clusters are the same as expected clusters
 */
bool compareClusters(IntegerVectorEncoding c1, IntegerVectorEncoding c2, 
                     IntegerVectorEncoding e1, IntegerVectorEncoding e2)
{
    if (c1.size() != e1.size() || c2.size() != e2.size())
        { return false; }

    for (int i = 0; i < c1.size(); i++)
    {
        if (c1.getClusterOfVertex(i) != e1.getClusterOfVertex(i))
        {
            return false;
        }
    }

    for (int i = 0; i < c2.size(); i++)
    {
        if (c2.getClusterOfVertex(i) != e2.getClusterOfVertex(i))
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Test if getting random solution works
 */
void TestClusterwiseCrossoverEngine::testCrossover(void)
{
    IntegerVectorEncoding p1(g);
    IntegerVectorEncoding p2(g);
    IntegerVectorEncoding child1(g), child2(g);

    // Initialize first parent
    p1.addToCluster(0, 0);
    p1.addToCluster(1, 1);
    p1.addToCluster(2, 2);
    p1.addToCluster(3, 3);
    p1.addToCluster(4, 1);
    p1.addToCluster(5, 0);
    // Initialize second parent
    p2.addToCluster(0, 4);
    p2.addToCluster(1, 5);
    p2.addToCluster(2, 5);
    p2.addToCluster(3, 4);
    p2.addToCluster(4, 6);
    p2.addToCluster(5, 5);

    p1.normalize();
    p2.normalize();

    // Crossover 1000 times, make sure all cases appear
    IntegerVectorEncoding case1_1(g), case2_1(g), case3_1(g);
    IntegerVectorEncoding case1_2(g), case2_2(g), case3_2(g);
    bool found1, found2, found3, foundOther;
    found1 = found2 = found3 = foundOther = false;

    case1_1.addToCluster(0, 0);
    case1_1.addToCluster(1, 1);
    case1_1.addToCluster(2, 2);
    case1_1.addToCluster(3, 0);
    case1_1.addToCluster(4, 1);
    case1_1.addToCluster(5, 1);
    case1_2.addToCluster(0, 0);
    case1_2.addToCluster(1, 1);
    case1_2.addToCluster(2, 1);
    case1_2.addToCluster(3, 2);
    case1_2.addToCluster(4, 3);
    case1_2.addToCluster(5, 0);

    case2_1.addToCluster(0, 0);
    case2_1.addToCluster(1, 1);
    case2_1.addToCluster(2, 1);
    case2_1.addToCluster(3, 2);
    case2_1.addToCluster(4, 3);
    case2_1.addToCluster(5, 0);
    case2_2.addToCluster(0, 0);
    case2_2.addToCluster(1, 1);
    case2_2.addToCluster(2, 2);
    case2_2.addToCluster(3, 0);
    case2_2.addToCluster(4, 1);
    case2_2.addToCluster(5, 1);

    case3_1.addToCluster(0, 0);
    case3_1.addToCluster(1, 1);
    case3_1.addToCluster(2, 1);
    case3_1.addToCluster(3, 2);
    case3_1.addToCluster(4, 3);
    case3_1.addToCluster(5, 1);
    case3_2.addToCluster(0, 0);
    case3_2.addToCluster(1, 1);
    case3_2.addToCluster(2, 2);
    case3_2.addToCluster(3, 0);
    case3_2.addToCluster(4, 1);
    case3_2.addToCluster(5, 0);

    for (int i = 0; i < 1000; i++)
    {
        testObj->crossover(p1, p2, child1, child2);
        if (compareClusters(child1, child2, case1_1, case1_2))
        {
            found1 = true;
        } 
        else if (compareClusters(child1, child2, case2_1, case2_2))
        {
            found2 = true;
        }
        else if (compareClusters(child1, child2, case3_1, case3_2))
        {
            found3 = true;
        }
        else
        {
            foundOther = true;
            break;
        }

    }
    CPPUNIT_ASSERT(found1);
    CPPUNIT_ASSERT(found2);
    CPPUNIT_ASSERT(found3);
    CPPUNIT_ASSERT(!foundOther);
}

