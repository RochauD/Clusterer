#include "TestLoggerSeverityLevel.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestLoggerSeverityLevel);

void TestLoggerSeverityLevel::setUp(void)
{

}

void TestLoggerSeverityLevel::tearDown(void)
{

}

void TestLoggerSeverityLevel::testReturnsAll(void)
{
    CPPUNIT_ASSERT(std::string("ALL") == severityLevelToString(SeverityLevel::ALL));
}

void TestLoggerSeverityLevel::testReturnsInfo(void)
{
    CPPUNIT_ASSERT(std::string("INFO") == severityLevelToString(SeverityLevel::INFO));
}

void TestLoggerSeverityLevel::testReturnsWarning(void)
{
    CPPUNIT_ASSERT(std::string("WARNING") == severityLevelToString(SeverityLevel::WARNING));
}

void TestLoggerSeverityLevel::testReturnsSevere(void)
{
    CPPUNIT_ASSERT(std::string("SEVERE") == severityLevelToString(SeverityLevel::SEVERE));
}

void TestLoggerSeverityLevel::testReturnsError(void)
{
    CPPUNIT_ASSERT(std::string("ERROR") == severityLevelToString(SeverityLevel::ERROR));
}

void TestLoggerSeverityLevel::testReturnsOff(void)
{
    CPPUNIT_ASSERT(std::string("OFF") == severityLevelToString(SeverityLevel::OFF));
}

void TestLoggerSeverityLevel::testReturnsEmptyOnInvalidInput(void)
{
    const unsigned char outOfBoundEnumId = 100;
    CPPUNIT_ASSERT(std::string("") == severityLevelToString(static_cast<SeverityLevel>(outOfBoundEnumId)));
}

// checkSeverityTypeMatch
void TestLoggerSeverityLevel::testLevelAllTypeDebug(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::ALL, SeverityType::DEBUG));
}

void TestLoggerSeverityLevel::testLevelAllTypeInfo(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::ALL, SeverityType::INFO));
}

void TestLoggerSeverityLevel::testLevelAllTypeWarning(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::ALL, SeverityType::WARNING));
}

void TestLoggerSeverityLevel::testLevelAllTypeSevere(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::ALL, SeverityType::SEVERE));
}

void TestLoggerSeverityLevel::testLevelAllTypeError(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::ALL, SeverityType::ERROR));
}


void TestLoggerSeverityLevel::testLevelInfoTypeDebug(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::INFO, SeverityType::DEBUG));
}

void TestLoggerSeverityLevel::testLevelInfoTypeInfo(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::INFO, SeverityType::INFO));
}

void TestLoggerSeverityLevel::testLevelInfoTypeWarning(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::INFO, SeverityType::WARNING));
}

void TestLoggerSeverityLevel::testLevelInfoTypeSevere(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::INFO, SeverityType::SEVERE));
}

void TestLoggerSeverityLevel::testLevelInfoTypeError(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::INFO, SeverityType::ERROR));
}


void TestLoggerSeverityLevel::testLevelWarningTypeDebug(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::WARNING, SeverityType::DEBUG));
}

void TestLoggerSeverityLevel::testLevelWarningTypeInfo(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::WARNING, SeverityType::INFO));
}

void TestLoggerSeverityLevel::testLevelWarningTypeWarning(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::WARNING, SeverityType::WARNING));
}

void TestLoggerSeverityLevel::testLevelWarningTypeSevere(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::WARNING, SeverityType::SEVERE));
}

void TestLoggerSeverityLevel::testLevelWarningTypeError(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::WARNING, SeverityType::ERROR));
}


void TestLoggerSeverityLevel::testLevelSevereTypeDebug(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::SEVERE, SeverityType::DEBUG));
}

void TestLoggerSeverityLevel::testLevelSevereTypeInfo(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::SEVERE, SeverityType::INFO));
}

void TestLoggerSeverityLevel::testLevelSevereTypeWarning(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::SEVERE, SeverityType::WARNING));
}

void TestLoggerSeverityLevel::testLevelSevereTypeSevere(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::SEVERE, SeverityType::SEVERE));
}

void TestLoggerSeverityLevel::testLevelSevereTypeError(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::SEVERE, SeverityType::ERROR));
}


void TestLoggerSeverityLevel::testLevelErrorTypeDebug(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::ERROR, SeverityType::DEBUG));
}

void TestLoggerSeverityLevel::testLevelErrorTypeInfo(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::ERROR, SeverityType::INFO));
}

void TestLoggerSeverityLevel::testLevelErrorTypeWarning(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::ERROR, SeverityType::WARNING));
}

void TestLoggerSeverityLevel::testLevelErrorTypeSevere(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::ERROR, SeverityType::SEVERE));
}

void TestLoggerSeverityLevel::testLevelErrorTypeError(void)
{
    CPPUNIT_ASSERT(true == checkSeverityTypeMatch(SeverityLevel::ERROR, SeverityType::ERROR));
}


void TestLoggerSeverityLevel::testLevelOffTypeDebug(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::OFF, SeverityType::DEBUG));
}

void TestLoggerSeverityLevel::testLevelOffTypeInfo(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::OFF, SeverityType::INFO));
}

void TestLoggerSeverityLevel::testLevelOffTypeWarning(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::OFF, SeverityType::WARNING));
}

void TestLoggerSeverityLevel::testLevelOffTypeSevere(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::OFF, SeverityType::SEVERE));
}

void TestLoggerSeverityLevel::testLevelOffTypeError(void)
{
    CPPUNIT_ASSERT(false == checkSeverityTypeMatch(SeverityLevel::OFF, SeverityType::ERROR));
}
