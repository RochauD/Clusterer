#ifndef TEST_BACKEND_FITNESS_ANALYZER_HPP
#define TEST_BACKEND_FITNESS_ANALYZER_HPP

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
#include "../include/FitnessAnalyzer.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/Graph.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestFitnessAnalyzer : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestFitnessAnalyzer);
        CPPUNIT_TEST(testAnalyzeSingleElementClustersOnly);
        CPPUNIT_TEST(testAnalyzeOneClusterOnly);
        CPPUNIT_TEST(testAnalyzeFullyConnectedGraphTwoClusters);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        // each vertex in a seperate cluster
        void testAnalyzeSingleElementClustersOnly(void);
        // each vertex in same cluster
        void testAnalyzeOneClusterOnly(void);
        // each vertex in one of two clusters
        void testAnalyzeTwoClusters(void);

    private:
        clb::FitnessAnalyzer fitnessAnalyzer;
	clb::Graph graph1;
	clb::Graph graph2;
};

#endif
