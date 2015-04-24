#ifndef TEST_FRONTEND_GRAPHCOORDTRANS_HPP
#define TEST_FRONTEND_GRAPHCOORDTRANS_HPP

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
#include "../include/GraphCoordinateTransformer.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;
using namespace clf;

class TestGraphCoordinateTransformer : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestGraphCoordinateTransformer);
        CPPUNIT_TEST(testObtainedCoordinates);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testObtainedCoordinates(void);

    private:
        void printSol(const ClusterEncoding&);
};

#endif