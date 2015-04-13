#ifndef TEST_BACKEND_GRAPH_READER_HPP
#define TEST_BACKEND_GRAPH_READER_HPP

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
#include "../include/GraphReader.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestGraphReader : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestGraphReader);
        CPPUNIT_TEST(testReadFileNonExistentFile);
        CPPUNIT_TEST(testReadTestGraph1);
        CPPUNIT_TEST(testReadTestGraph2);
        CPPUNIT_TEST(testReadTestZachary);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testReadFileNonExistentFile(void);
        void testReadTestGraph1(void);
        void testReadTestGraph2(void);
        void testReadTestZachary(void);
    private:

};

#endif
