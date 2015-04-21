#ifndef TEST_BACKEND_VERTEX_HPP
#define TEST_BACKEND_VERTEX_HPP

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
#include "../include/Vertex.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestVertex : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestVertex);
        CPPUNIT_TEST(testGetVNumber);
        CPPUNIT_TEST(testSetVNumber);
        CPPUNIT_TEST(testAddHasNeighbor);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testGetVNumber(void);
        void testSetVNumber(void);
        void testAddHasNeighbor(void);

    private:

};

#endif
