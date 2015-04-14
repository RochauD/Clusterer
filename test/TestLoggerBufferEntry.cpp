#include "TestLoggerBufferEntry.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestLoggerBufferEntry);

void TestLoggerBufferEntry::setUp(void)
{

}

void TestLoggerBufferEntry::tearDown(void)
{

}

void TestLoggerBufferEntry::testLoggerBufferEntry(void)
{
    std::chrono::system_clock::time_point testTimePoint = std::chrono::system_clock::now();
    LoggerBufferEntry testEntry(SeverityType::INFO, testTimePoint, std::string("test message"));

    CPPUNIT_ASSERT(SeverityType::INFO == testEntry.severityType);
    CPPUNIT_ASSERT(testTimePoint == testEntry.logTimePoint);
    CPPUNIT_ASSERT(std::string("test message") == testEntry.logMessage);
}
