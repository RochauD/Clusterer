#include "TestIntegerVectorEncoding.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/Graph.hpp"
#include "../include/Vertex.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestIntegerVectorEncoding);

/**
 * @brief Sets up an encoding object with a sample graph
 */
void TestIntegerVectorEncoding::setUp(void)
{
    Graph g;
    Vertex v0(0);
    Vertex v1(1);
    Vertex v2(2);

    g.addVertex(v0);
    g.addVertex(v1);
    g.addVertex(v2);

    testObj = new IntegerVectorEncoding(g);
}

/**
 * @brief Deletes the sample object
 */
void TestIntegerVectorEncoding::tearDown(void)
{
    delete testObj;
}

/**
 * @brief Test if setting and getting the cluster of a vertex works
 */
void TestIntegerVectorEncoding::testSettersGetters(void)
{
    testObj->addToCluster(0, 1);
    testObj->addToCluster(1, 2);
    testObj->addToCluster(2, 1);

    CPPUNIT_ASSERT(1 == testObj->getClusterOfVertex(0));
    CPPUNIT_ASSERT(2 == testObj->getClusterOfVertex(1));
    CPPUNIT_ASSERT(1 == testObj->getClusterOfVertex(2));

    std::vector<VertexId> c1 = testObj->getVerticesInCluster(1);
    CPPUNIT_ASSERT(2 == c1.size());
    CPPUNIT_ASSERT(0 == c1[0]);
    CPPUNIT_ASSERT(2 == c1[1]);
}

/**
 * @brief Test the normalization procedure and getEncoding
 */
void TestIntegerVectorEncoding::testNormalization(void)
{
    testObj->addToCluster(0, 1);
    testObj->addToCluster(1, 2);
    testObj->addToCluster(2, 1);

    CPPUNIT_ASSERT(0 == testObj->normalize());
    ClusterEncoding::Encoding enc = testObj->getEncoding();
    CPPUNIT_ASSERT(0 == enc[0]);
    CPPUNIT_ASSERT(1 == enc[1]);
    CPPUNIT_ASSERT(0 == enc[2]);

}