#include "TestVertex.hpp"
#include "../include/ErrorLogger.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( TestVertex );

void TestVertex::setUp(void) {
}

void TestVertex::tearDown(void) {
}

void TestVertex::testFail(void) {
    CPPUNIT_ASSERT(false);
}