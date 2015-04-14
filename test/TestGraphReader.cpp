#include "TestGraphReader.hpp"
#include "../include/Graph.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestGraphReader);

// helper function
bool compare(const std::pair<std::pair<VertexId, VertexId>, double >& e1,
             const std::pair<std::pair<VertexId, VertexId>, double >& e2)
{
    if (e1.first.first == e2.first.first)
    {
        if (e1.first.second == e2.first.second)
        {
            return (e1.second < e2.second);
        }
        else
        {
            return (e1.first.second < e2.first.second);
        }
        return true;
    }
    else
    {
        return (e1.first.first < e2.first.first);
    }
}

void TestGraphReader::setUp(void)
{

}

void TestGraphReader::tearDown(void)
{

}

void TestGraphReader::testReadFileNonExistentFile(void)
{
    Graph g;
    GraphReader reader(&g);
    CPPUNIT_ASSERT(false == reader.readFile("../test_files/FileNonExistentFile.file"));
}

void TestGraphReader::testReadTestGraph1(void)
{
    Graph g;
    GraphReader reader(&g);
    CPPUNIT_ASSERT(true == reader.readFile("../test_files/Graph1.txt"));
    std::vector < std::pair<std::pair<VertexId, VertexId>, double>> compareVec =
    {
        std::make_pair(std::make_pair(1, 2), 20),
        std::make_pair(std::make_pair(1, 3), 10),
        std::make_pair(std::make_pair(2, 3), 20),
        std::make_pair(std::make_pair(1, 4), 15),
        std::make_pair(std::make_pair(2, 4), 16),
        std::make_pair(std::make_pair(3, 4), 18),
        std::make_pair(std::make_pair(1, 5), 26),
        std::make_pair(std::make_pair(1, 6), 19),
        std::make_pair(std::make_pair(1, 7), 19),
        std::make_pair(std::make_pair(5, 7), 16),
        std::make_pair(std::make_pair(6, 7), 15),
        std::make_pair(std::make_pair(1, 8), 12),
        std::make_pair(std::make_pair(2, 8), 16),
        std::make_pair(std::make_pair(3, 8), 33),
        std::make_pair(std::make_pair(4, 8), 25),
        std::make_pair(std::make_pair(1, 9), 28),
        std::make_pair(std::make_pair(3, 9), 16),
        std::make_pair(std::make_pair(3, 10), 14),
        std::make_pair(std::make_pair(1, 11), 12),
        std::make_pair(std::make_pair(5, 11), 19),
        std::make_pair(std::make_pair(6, 11), 18),
        std::make_pair(std::make_pair(1, 12), 24),
        std::make_pair(std::make_pair(1, 13), 36),
        std::make_pair(std::make_pair(4, 13), 21),
        std::make_pair(std::make_pair(1, 14), 33),
        std::make_pair(std::make_pair(2, 14), 35),
        std::make_pair(std::make_pair(3, 14), 29),
        std::make_pair(std::make_pair(4, 14), 20),
        std::make_pair(std::make_pair(6, 17), 16),
        std::make_pair(std::make_pair(7, 17), 19),
        std::make_pair(std::make_pair(1, 18), 17),
        std::make_pair(std::make_pair(2, 18), 12),
        std::make_pair(std::make_pair(1, 20), 19),
        std::make_pair(std::make_pair(2, 20), 24),
        std::make_pair(std::make_pair(1, 22), 31),
        std::make_pair(std::make_pair(2, 22), 26),
        std::make_pair(std::make_pair(24, 26), 23),
        std::make_pair(std::make_pair(25, 26), 25),
        std::make_pair(std::make_pair(3, 28), 24),
        std::make_pair(std::make_pair(24, 28), 29),
        std::make_pair(std::make_pair(25, 28), 32),
        std::make_pair(std::make_pair(3, 29), 13),
        std::make_pair(std::make_pair(24, 30), 29),
        std::make_pair(std::make_pair(27, 30), 18),
        std::make_pair(std::make_pair(2, 31), 17),
        std::make_pair(std::make_pair(9, 31), 12),
        std::make_pair(std::make_pair(1, 32), 13),
        std::make_pair(std::make_pair(25, 32), 14),
        std::make_pair(std::make_pair(26, 32), 19),
        std::make_pair(std::make_pair(29, 32), 16),
        std::make_pair(std::make_pair(3, 33), 15),
        std::make_pair(std::make_pair(9, 33), 19),
        std::make_pair(std::make_pair(15, 33), 19),
        std::make_pair(std::make_pair(16, 33), 18),
        std::make_pair(std::make_pair(19, 33), 20),
        std::make_pair(std::make_pair(21, 33), 21),
        std::make_pair(std::make_pair(23, 33), 22),
        std::make_pair(std::make_pair(24, 33), 23),
        std::make_pair(std::make_pair(30, 33), 24),
        std::make_pair(std::make_pair(31, 33), 29),
        std::make_pair(std::make_pair(32, 33), 30),
        std::make_pair(std::make_pair(9, 34), 33),
        std::make_pair(std::make_pair(10, 34), 26),
        std::make_pair(std::make_pair(14, 34), 28),
        std::make_pair(std::make_pair(15, 34), 23),
        std::make_pair(std::make_pair(16, 34), 22),
        std::make_pair(std::make_pair(19, 34), 21),
        std::make_pair(std::make_pair(20, 34), 25),
        std::make_pair(std::make_pair(21, 34), 26),
        std::make_pair(std::make_pair(23, 34), 29),
        std::make_pair(std::make_pair(24, 34), 30),
        std::make_pair(std::make_pair(27, 34), 13),
        std::make_pair(std::make_pair(28, 34), 16),
        std::make_pair(std::make_pair(29, 34), 17),
        std::make_pair(std::make_pair(30, 34), 18),
        std::make_pair(std::make_pair(31, 34), 19),
        std::make_pair(std::make_pair(32, 34), 20),
        std::make_pair(std::make_pair(33, 34), 21.67)
    };
    std::sort(compareVec.begin(), compareVec.end(), compare);
    auto vec = g.getEdgesAndWeights();
    std::sort(vec.begin(), vec.end(), compare);
    CPPUNIT_ASSERT(vec == compareVec);
}

void TestGraphReader::testReadTestGraph2(void)
{
    Graph g;
    GraphReader reader(&g);
    CPPUNIT_ASSERT(true == reader.readFile("../test_files/Graph2.txt"));
    std::vector < std::pair<std::pair<VertexId, VertexId>, double>> compareVec =
    {
        std::make_pair(std::make_pair(1, 2), 20),
        std::make_pair(std::make_pair(1, 3), 10),
        std::make_pair(std::make_pair(2, 3), 20),
        std::make_pair(std::make_pair(1, 4), 15),
        std::make_pair(std::make_pair(2, 4), 16),
        std::make_pair(std::make_pair(10, 15), 30),
        std::make_pair(std::make_pair(14, 15), 36)
    };
    std::sort(compareVec.begin(), compareVec.end(), compare);
    auto vec = g.getEdgesAndWeights();
    std::sort(vec.begin(), vec.end(), compare);
    CPPUNIT_ASSERT(vec == compareVec);
}

void TestGraphReader::testReadTestZachary(void)
{
    Graph g;
    GraphReader reader(&g);
    CPPUNIT_ASSERT(true == reader.readFile("../test_files/out.ucidata-zachary"));
    std::vector < std::pair<std::pair<VertexId, VertexId>, double>> compareVec =
    {
        std::make_pair(std::make_pair(1, 2), 0),
        std::make_pair(std::make_pair(1, 3), 0),
        std::make_pair(std::make_pair(2, 3), 0),
        std::make_pair(std::make_pair(1, 4), 0),
        std::make_pair(std::make_pair(2, 4), 0),
        std::make_pair(std::make_pair(3, 4), 0),
        std::make_pair(std::make_pair(1, 5), 0),
        std::make_pair(std::make_pair(1, 6), 0),
        std::make_pair(std::make_pair(1, 7), 0),
        std::make_pair(std::make_pair(5, 7), 0),
        std::make_pair(std::make_pair(6, 7), 0),
        std::make_pair(std::make_pair(1, 8), 0),
        std::make_pair(std::make_pair(2, 8), 0),
        std::make_pair(std::make_pair(3, 8), 0),
        std::make_pair(std::make_pair(4, 8), 0),
        std::make_pair(std::make_pair(1, 9), 0),
        std::make_pair(std::make_pair(3, 9), 0),
        std::make_pair(std::make_pair(3, 10), 0),
        std::make_pair(std::make_pair(1, 11), 0),
        std::make_pair(std::make_pair(5, 11), 0),
        std::make_pair(std::make_pair(6, 11), 0),
        std::make_pair(std::make_pair(1, 12), 0),
        std::make_pair(std::make_pair(1, 13), 0),
        std::make_pair(std::make_pair(4, 13), 0),
        std::make_pair(std::make_pair(1, 14), 0),
        std::make_pair(std::make_pair(2, 14), 0),
        std::make_pair(std::make_pair(3, 14), 0),
        std::make_pair(std::make_pair(4, 14), 0),
        std::make_pair(std::make_pair(6, 17), 0),
        std::make_pair(std::make_pair(7, 17), 0),
        std::make_pair(std::make_pair(1, 18), 0),
        std::make_pair(std::make_pair(2, 18), 0),
        std::make_pair(std::make_pair(1, 20), 0),
        std::make_pair(std::make_pair(2, 20), 0),
        std::make_pair(std::make_pair(1, 22), 0),
        std::make_pair(std::make_pair(2, 22), 0),
        std::make_pair(std::make_pair(24, 26), 0),
        std::make_pair(std::make_pair(25, 26), 0),
        std::make_pair(std::make_pair(3, 28), 0),
        std::make_pair(std::make_pair(24, 28), 0),
        std::make_pair(std::make_pair(25, 28), 0),
        std::make_pair(std::make_pair(3, 29), 0),
        std::make_pair(std::make_pair(24, 30), 0),
        std::make_pair(std::make_pair(27, 30), 0),
        std::make_pair(std::make_pair(2, 31), 0),
        std::make_pair(std::make_pair(9, 31), 0),
        std::make_pair(std::make_pair(1, 32), 0),
        std::make_pair(std::make_pair(25, 32), 0),
        std::make_pair(std::make_pair(26, 32), 0),
        std::make_pair(std::make_pair(29, 32), 0),
        std::make_pair(std::make_pair(3, 33), 0),
        std::make_pair(std::make_pair(9, 33), 0),
        std::make_pair(std::make_pair(15, 33), 0),
        std::make_pair(std::make_pair(16, 33), 0),
        std::make_pair(std::make_pair(19, 33), 0),
        std::make_pair(std::make_pair(21, 33), 0),
        std::make_pair(std::make_pair(23, 33), 0),
        std::make_pair(std::make_pair(24, 33), 0),
        std::make_pair(std::make_pair(30, 33), 0),
        std::make_pair(std::make_pair(31, 33), 0),
        std::make_pair(std::make_pair(32, 33), 0),
        std::make_pair(std::make_pair(9, 34), 0),
        std::make_pair(std::make_pair(10, 34), 0),
        std::make_pair(std::make_pair(14, 34), 0),
        std::make_pair(std::make_pair(15, 34), 0),
        std::make_pair(std::make_pair(16, 34), 0),
        std::make_pair(std::make_pair(19, 34), 0),
        std::make_pair(std::make_pair(20, 34), 0),
        std::make_pair(std::make_pair(21, 34), 0),
        std::make_pair(std::make_pair(23, 34), 0),
        std::make_pair(std::make_pair(24, 34), 0),
        std::make_pair(std::make_pair(27, 34), 0),
        std::make_pair(std::make_pair(28, 34), 0),
        std::make_pair(std::make_pair(29, 34), 0),
        std::make_pair(std::make_pair(30, 34), 0),
        std::make_pair(std::make_pair(31, 34), 0),
        std::make_pair(std::make_pair(32, 34), 0),
        std::make_pair(std::make_pair(33, 34), 0)
    };
    std::sort(compareVec.begin(), compareVec.end(), compare);
    auto vec = g.getEdgesAndWeights();
    std::sort(vec.begin(), vec.end(), compare);
    CPPUNIT_ASSERT(vec == compareVec);
}
