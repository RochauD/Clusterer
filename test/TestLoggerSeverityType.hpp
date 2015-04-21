#ifndef TEST_CLUSTERER_COMMON_LOGGER_SEVERITY_TYPE_HPP
#define TEST_CLUSTERER_COMMON_LOGGER_SEVERITY_TYPE_HPP

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
#include "../include/LoggerSeverityType.hpp"


using namespace CppUnit;
using namespace std;
using namespace clc;

class TestLoggerSeverityType : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestLoggerSeverityType);
        CPPUNIT_TEST(testReturnsDebug);
        CPPUNIT_TEST(testReturnsInfo);
        CPPUNIT_TEST(testReturnsWarning);
        CPPUNIT_TEST(testReturnsSevere);
        CPPUNIT_TEST(testReturnsError);
        CPPUNIT_TEST(testReturnsEmptyOnInvalidInput);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testReturnsDebug(void);
        void testReturnsInfo(void);
        void testReturnsWarning(void);
        void testReturnsSevere(void);
        void testReturnsError(void);
        void testReturnsEmptyOnInvalidInput(void);

    private:

};

#endif
