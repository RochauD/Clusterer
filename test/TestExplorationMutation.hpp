#ifndef TEST_BACKEND_MUTATION_HPP
#define TEST_BACKEND_MUTATION_HPP

// standard headers
#include <random>
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
#include "../include/ClusterEncoding.hpp"
#include "../include/ExplorationMutation.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestExplorationMutation : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestExplorationMutation);
        CPPUNIT_TEST(testMutateAndSplitFunction);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        // test mutation function
        void testMutateAndSplitFunction(void);

    private:
        clb::ExplorationMutation mutator;
        void printSol(const ClusterEncoding&,int);
};

#endif


