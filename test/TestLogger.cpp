#include "TestLogger.hpp"

#include <fstream>
#include <sstream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestLogger);

int counter = 0;

void TestLogger::setUp(void)
{
    counter++;
    std::string filename = "test" + std::to_string(counter) + ".log";

    // clear file
    std::ofstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc);
    file.close();

    std::unique_ptr<LoggingPolicyFile> uPtr(new LoggingPolicyFile(filename));
    this->logger = new Logger<LoggingPolicyFile>(std::move(uPtr), SeverityLevel::ALL);
}

void TestLogger::tearDown(void)
{
    if (this->logger != nullptr)
    {
        delete this->logger;
    }
}

void TestLogger::testGetSeverityLevel(void)
{
    CPPUNIT_ASSERT(this->logger->getSeverityLevel() == SeverityLevel::ALL);
}

void TestLogger::testSetSeverityLevel(void)
{
    this->logger->setSeverityLevel(SeverityLevel::INFO);
    CPPUNIT_ASSERT(this->logger->getSeverityLevel() == SeverityLevel::INFO);
}

void TestLogger::testLog(void)
{
    std::string testString = "test";
    int testInt = 10001;
    double testDouble = 1.0101;
    this->logger->log(SeverityType::INFO, testString, " ", testInt, " ", testDouble);

    delete this->logger;
    this->logger = nullptr;

    std::string filename = "test" + std::to_string(counter) + ".log";
    std::ifstream file(filename);
    std::string buffer;

    if (!std::getline(file, buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    file.close();

    std::stringstream ss(buffer);
    if (!(ss >> buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    if (!(ss >> buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    if (!(ss >> buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    if (!(ss >> buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    else
    {
        CPPUNIT_ASSERT("INFO" == buffer);
    }
    if (!(ss >> buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    if (!(ss >> buffer))
    {
        CPPUNIT_ASSERT(false);
    }
    else
    {
        CPPUNIT_ASSERT("test" == buffer);
    }
    int loadInt;
    if (!(ss >> loadInt))
    {
        CPPUNIT_ASSERT(false);
    }
    else
    {
        CPPUNIT_ASSERT(testInt == loadInt);
    }
    double loadDouble;
    if (!(ss >> loadDouble))
    {
        CPPUNIT_ASSERT(false);
    }
    else
    {
        CPPUNIT_ASSERT(testDouble <  loadDouble + std::numeric_limits<double>::epsilon() &&
                       testDouble >  loadDouble - std::numeric_limits<double>::epsilon());
    }
}
