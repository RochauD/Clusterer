#include "TestGraph.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestGraph);

void TestGraph::setUp(void)
{
    testg = new Graph();
}

void TestGraph::tearDown(void)
{
    delete testg;
}

void TestGraph::testGetMethods(void)
{
    CPPUNIT_ASSERT(false);
}

void TestGraph::testAddMethods(void)
{
    CPPUNIT_ASSERT(false);
}


