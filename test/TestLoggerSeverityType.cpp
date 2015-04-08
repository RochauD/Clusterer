#include "TestLoggerSeverityType.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestLoggerSeverityType);

void TestLoggerSeverityType::setUp(void)
{

}

void TestLoggerSeverityType::tearDown(void)
{

}

void TestLoggerSeverityType::testReturnsDebug(void)
{
    CPPUNIT_ASSERT(std::string("DEBUG") == severityTypeToString(SeverityType::DEBUG));
}

void TestLoggerSeverityType::testReturnsInfo(void)
{
    CPPUNIT_ASSERT(std::string("INFO") == severityTypeToString(SeverityType::INFO));
}

void TestLoggerSeverityType::testReturnsWarning(void)
{
    CPPUNIT_ASSERT(std::string("WARNING") == severityTypeToString(SeverityType::WARNING));
}

void TestLoggerSeverityType::testReturnsSevere(void)
{
    CPPUNIT_ASSERT(std::string("SEVERE") == severityTypeToString(SeverityType::SEVERE));
}

void TestLoggerSeverityType::testReturnsError(void)
{
    CPPUNIT_ASSERT(std::string("ERROR") == severityTypeToString(SeverityType::ERROR));
}

void TestLoggerSeverityType::testReturnsEmptyOnInvalidInput(void)
{
    const unsigned char outOfBoundEnumId = 100;
    CPPUNIT_ASSERT(std::string("") == severityTypeToString(static_cast<SeverityType>(outOfBoundEnumId)));
}
