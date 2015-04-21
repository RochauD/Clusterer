#ifndef TEST_CLUSTERER_COMMON_LOGGER_HPP
#define TEST_CLUSTERER_COMMON_LOGGER_HPP

// standard headers

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
#include "../include/Logger.hpp"
#include "../include/LoggingPolicyFile.hpp"

using namespace CppUnit;
using namespace std;
using namespace clc;

class TestLogger : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestLogger);
        CPPUNIT_TEST(testGetSeverityLevel);
        CPPUNIT_TEST(testSetSeverityLevel);
        CPPUNIT_TEST(testLog);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testGetSeverityLevel(void);
        void testSetSeverityLevel(void);
        void testLog(void);

    private:
        Logger<LoggingPolicyFile>* logger;
};

#endif
