#ifndef TEST_BACKEND_CLUSTERING_POPULATION_ANALYZER_HPP
#define TEST_BACKEND_CLUSTERING_POPULATION_ANALYZER_HPP

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

//internal headers
#include "../include/Graph.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/IntegerEncodingInitializer.hpp"
#include "../include/FitnessAnalyzer.hpp"
#include "../include/ClusteringPopulationAnalyzer.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestClusteringPopulationAnalyzer : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestClusteringPopulationAnalyzer);
        CPPUNIT_TEST(testEvaluatePopulationOneThread);
        CPPUNIT_TEST(testEvaluatePopulationTwoThreads);
        CPPUNIT_TEST(testEvaluatePopulationThreeThreads);
        CPPUNIT_TEST(testEvaluatePopulationFourThreads);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testEvaluatePopulationOneThread(void);
        void testEvaluatePopulationTwoThreads(void);
        void testEvaluatePopulationThreeThreads(void);
        void testEvaluatePopulationFourThreads(void);

    private:

};

#endif
