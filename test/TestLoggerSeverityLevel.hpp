#ifndef TEST_CLUSTERER_COMMON_LOGGER_SEVERITY_LEVEL_HPP
#define TEST_CLUSTERER_COMMON_LOGGER_SEVERITY_LEVEL_HPP

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
#include "../include/LoggerSeverityLevel.hpp"


using namespace CppUnit;
using namespace std;
using namespace clc;

class TestLoggerSeverityLevel : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestLoggerSeverityLevel);
        CPPUNIT_TEST(testReturnsAll);
        CPPUNIT_TEST(testReturnsInfo);
        CPPUNIT_TEST(testReturnsWarning);
        CPPUNIT_TEST(testReturnsSevere);
        CPPUNIT_TEST(testReturnsError);
        CPPUNIT_TEST(testReturnsOff);
        CPPUNIT_TEST(testReturnsEmptyOnInvalidInput);
        CPPUNIT_TEST(testLevelAllTypeDebug);
        CPPUNIT_TEST(testLevelAllTypeInfo);
        CPPUNIT_TEST(testLevelAllTypeWarning);
        CPPUNIT_TEST(testLevelAllTypeSevere);
        CPPUNIT_TEST(testLevelAllTypeError);
        CPPUNIT_TEST(testLevelInfoTypeDebug);
        CPPUNIT_TEST(testLevelInfoTypeInfo);
        CPPUNIT_TEST(testLevelInfoTypeWarning);
        CPPUNIT_TEST(testLevelInfoTypeSevere);
        CPPUNIT_TEST(testLevelInfoTypeError);
        CPPUNIT_TEST(testLevelWarningTypeDebug);
        CPPUNIT_TEST(testLevelWarningTypeInfo);
        CPPUNIT_TEST(testLevelWarningTypeWarning);
        CPPUNIT_TEST(testLevelWarningTypeSevere);
        CPPUNIT_TEST(testLevelWarningTypeError);
        CPPUNIT_TEST(testLevelSevereTypeDebug);
        CPPUNIT_TEST(testLevelSevereTypeInfo);
        CPPUNIT_TEST(testLevelSevereTypeWarning);
        CPPUNIT_TEST(testLevelSevereTypeSevere);
        CPPUNIT_TEST(testLevelSevereTypeError);
        CPPUNIT_TEST(testLevelErrorTypeDebug);
        CPPUNIT_TEST(testLevelErrorTypeInfo);
        CPPUNIT_TEST(testLevelErrorTypeWarning);
        CPPUNIT_TEST(testLevelErrorTypeSevere);
        CPPUNIT_TEST(testLevelErrorTypeError);
        CPPUNIT_TEST(testLevelOffTypeDebug);
        CPPUNIT_TEST(testLevelOffTypeInfo);
        CPPUNIT_TEST(testLevelOffTypeWarning);
        CPPUNIT_TEST(testLevelOffTypeSevere);
        CPPUNIT_TEST(testLevelOffTypeError);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testReturnsAll(void);
        void testReturnsInfo(void);
        void testReturnsWarning(void);
        void testReturnsSevere(void);
        void testReturnsError(void);
        void testReturnsOff(void);
        void testReturnsEmptyOnInvalidInput(void);

        // CheckSeverityTypeMatch
        void testLevelAllTypeDebug(void);
        void testLevelAllTypeInfo(void);
        void testLevelAllTypeWarning(void);
        void testLevelAllTypeSevere(void);
        void testLevelAllTypeError(void);

        void testLevelInfoTypeDebug(void);
        void testLevelInfoTypeInfo(void);
        void testLevelInfoTypeWarning(void);
        void testLevelInfoTypeSevere(void);
        void testLevelInfoTypeError(void);

        void testLevelWarningTypeDebug(void);
        void testLevelWarningTypeInfo(void);
        void testLevelWarningTypeWarning(void);
        void testLevelWarningTypeSevere(void);
        void testLevelWarningTypeError(void);

        void testLevelSevereTypeDebug(void);
        void testLevelSevereTypeInfo(void);
        void testLevelSevereTypeWarning(void);
        void testLevelSevereTypeSevere(void);
        void testLevelSevereTypeError(void);

        void testLevelErrorTypeDebug(void);
        void testLevelErrorTypeInfo(void);
        void testLevelErrorTypeWarning(void);
        void testLevelErrorTypeSevere(void);
        void testLevelErrorTypeError(void);

        void testLevelOffTypeDebug(void);
        void testLevelOffTypeInfo(void);
        void testLevelOffTypeWarning(void);
        void testLevelOffTypeSevere(void);
        void testLevelOffTypeError(void);

    private:

};

#endif
