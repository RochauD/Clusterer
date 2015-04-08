#ifndef TEST_CLUSTERER_COMMON_LOGGER_BUFFER_ENTRY_HPP
#define TEST_CLUSTERER_COMMON_LOGGER_BUFFER_ENTRY_HPP

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
#include "../include/LoggerBufferEntry.hpp"


using namespace CppUnit;
using namespace std;
using namespace clc;

class TestLoggerBufferEntry : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestLoggerBufferEntry);
        CPPUNIT_TEST(testLoggerBufferEntry);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testLoggerBufferEntry(void);

    private:

};

#endif
