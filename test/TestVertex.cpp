#include "TestVertex.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestVertex);

void TestVertex::setUp(void)
{
}

void TestVertex::tearDown(void)
{
}

void TestVertex::testGetVNumber(void)
{
    Vertex v(100);
    CPPUNIT_ASSERT(100 == v.getVNumber());
}

void TestVertex::testSetVNumber(void)
{
    Vertex v;
    v.setVNumber(100);
    CPPUNIT_ASSERT(100 == v.getVNumber());
}

void TestVertex::testAddHasNeighbor(void)
{
    Vertex v1(100);
    Vertex v2(101);
    v1.addNeighbor(v2);
    CPPUNIT_ASSERT(true == v1.hasNeighbor(v2));
}
