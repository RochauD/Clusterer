#ifndef TEST_BACKEND_GRAPH_HPP
#define TEST_BACKEND_GRAPH_HPP

// standard headers
#include <typeinfo>
// external headers
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
// internal headers
#include "../include/Graph.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestGraph : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestGraph);
        CPPUNIT_TEST(testGetNoVerticesReturnsZeroOnEmptyGraph);
        CPPUNIT_TEST(testGetNoVerticesWorks);
        CPPUNIT_TEST(testGetNoEdgesReturnsZeroOnEmptyGraph);
        CPPUNIT_TEST(testGetNoEdgesWorks);
        CPPUNIT_TEST(testAddVertex);
        CPPUNIT_TEST(testAddEdgeWithoutWeight);
        CPPUNIT_TEST(testAddEdgeWithWeight);
        CPPUNIT_TEST(testSetEdgeWeight);
        CPPUNIT_TEST(testGetEdgeWeight);
        CPPUNIT_TEST(testGetEdgeWeightNonExistentEdge);
        CPPUNIT_TEST(testGetVertices);
        CPPUNIT_TEST(testGetVerticesOnEmptyGraph);
        CPPUNIT_TEST(testGetEdges);
        CPPUNIT_TEST(testGetEdgesOnEmptyGraph);
        CPPUNIT_TEST(testGetEdgesAndWeights);
        CPPUNIT_TEST(testGetEdgesAndWeightsOnEmptyGraph);
        CPPUNIT_TEST(testGetNeighbors);
        CPPUNIT_TEST(testGetNeighborsOnThreeNodeGraph);
        CPPUNIT_TEST(testGetNeighborsOnEmptyGraph);
        CPPUNIT_TEST(testExistsEdge);
        CPPUNIT_TEST(testExistsEdgeOnEmptyGraph);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testGetNoVerticesReturnsZeroOnEmptyGraph(void);
        void testGetNoVerticesWorks(void);
        void testGetNoEdgesReturnsZeroOnEmptyGraph(void);
        void testGetNoEdgesWorks(void);
        void testAddVertex(void);
        void testAddEdgeWithoutWeight(void);
        void testAddEdgeWithWeight(void);
        void testSetEdgeWeight(void);
        void testGetEdgeWeight(void);
        void testGetEdgeWeightNonExistentEdge(void);
        void testGetVertices(void);
        void testGetVerticesOnEmptyGraph(void);
        void testGetEdges(void);
        void testGetEdgesOnEmptyGraph(void);
        void testGetEdgesAndWeights(void);
        void testGetEdgesAndWeightsOnEmptyGraph(void);
        void testGetNeighbors(void);
        void testGetNeighborsOnThreeNodeGraph(void);
        void testGetNeighborsOnEmptyGraph(void);
        void testExistsEdge(void);
        void testExistsEdgeOnEmptyGraph(void);

    private:

};

#endif
