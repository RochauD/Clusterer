#ifndef TEST_BASIC_CONF_HPP
#define TEST_BASIC_CONF_HPP

#include <iostream>
#include <fstream>

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

#include "../include/UniformCrossoverEngine.hpp"

using namespace CppUnit;
using namespace std;
using namespace clb;

class TestUniformCrossoverEngine : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestUniformCrossoverEngine);

        CPPUNIT_TEST(testCrossover);

        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testCrossover(void);

    private:
        UniformCrossoverEngine *testObj;
};

#endif
