#include "TestSelector.hpp"
#include "../include/Selector.hpp"
#include <cstring>
#include <cstdint>
CPPUNIT_TEST_SUITE_REGISTRATION(TestSelector);

/**
 * @brief Sets up an encoding object with a sample graph
 */
void TestSelector::setUp(void)
{
    data = new std::vector<std::pair<int, double>>();
    
    data->push_back(std::make_pair(0, 0.8));
    data->push_back(std::make_pair(1, 1.2));
    data->push_back(std::make_pair(2, 0.5));
    data->push_back(std::make_pair(3, 1.7));

    testObj = new Selector<std::vector<std::pair<int, double>>>(data);
}

/**
 * @brief Deletes the sample object
 */
void TestSelector::tearDown(void)
{
    delete data;
    delete testObj;
}


/**
 * @brief Test if selecting two parents works
 */
void TestSelector::testSelect(void)
{
    bool selected[4];
    memset(selected, 0, sizeof(selected));

    for (int i = 0; i < 1000; i++)
    {
        std::pair<uint64_t, uint64_t> result = testObj->selectTwoClusters();
        selected[result.first] = selected[result.second] = true;
    }

    CPPUNIT_ASSERT(selected[0]);
    CPPUNIT_ASSERT(selected[1]);
    CPPUNIT_ASSERT(selected[2]);
    CPPUNIT_ASSERT(selected[3]);
}

