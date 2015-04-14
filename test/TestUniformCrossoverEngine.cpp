#include "TestUniformCrossoverEngine.hpp"
#include "../include/UniformCrossoverEngine.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestUniformCrossoverEngine);

/**
 * @brief Sets up an encoding object with a sample graph
 */
void TestUniformCrossoverEngine::setUp(void)
{
    testObj = new UniformCrossoverEngine;
}

/**
 * @brief Deletes the sample object
 */
void TestUniformCrossoverEngine::tearDown(void)
{
    delete testObj;
}

/**
 * @brief Test if getting random solution works
 */
void TestUniformCrossoverEngine::testCrossover(void)
{
    CPPUNIT_ASSERT(false);

}

