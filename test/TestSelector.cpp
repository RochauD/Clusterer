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
    data = new std::vector<PopulationMember<int, double>>();
    PopulationMember<int, double> member;
    member.fitnessValue = 0.8;
    member.populationEncoding = 0;
    data->push_back(member);
    member.fitnessValue = 1.2;
    member.populationEncoding = 1;
    data->push_back(member);
    member.fitnessValue = 0.5;
    member.populationEncoding = 2;
    data->push_back(member);
    member.fitnessValue = 1.7;
    member.populationEncoding = 3;
    data->push_back(member);

    rng = new std::mt19937();
    testObj = new Selector<std::vector<PopulationMember<int, double>>>(data, rng);
}

/**
 * @brief Deletes the sample object
 */
void TestSelector::tearDown(void)
{
    delete data;
    delete testObj;
    delete rng;
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

