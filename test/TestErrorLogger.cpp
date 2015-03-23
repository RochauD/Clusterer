#include "TestErrorLogger.hpp"
#include "../include/ErrorLogger.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( TestErrorLogger );

void TestErrorLogger::setUp(void) {
}

void TestErrorLogger::tearDown(void) {
}

void TestErrorLogger::testFail(void) {
    CPPUNIT_ASSERT(false);
}