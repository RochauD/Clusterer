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

    int64_t ofs = g.getOffset();
    if(ofs == -1) {
        // no vertices added to the graph.
        return;
    }

    std::vector < std::pair<std::pair<VertexId, VertexId>, double>> compareVec =
    {
        std::make_pair(std::make_pair(1-ofs, 2-ofs), 20),
        std::make_pair(std::make_pair(1-ofs, 3-ofs), 10),
        std::make_pair(std::make_pair(2-ofs, 3-ofs), 20),
        std::make_pair(std::make_pair(1-ofs, 4-ofs), 15),
        std::make_pair(std::make_pair(2-ofs, 4-ofs), 16),
        std::make_pair(std::make_pair(3-ofs, 4-ofs), 18),
        std::make_pair(std::make_pair(1-ofs, 5-ofs), 26),
        std::make_pair(std::make_pair(1-ofs, 6-ofs), 19),
        std::make_pair(std::make_pair(1-ofs, 7-ofs), 19),
        std::make_pair(std::make_pair(5-ofs, 7-ofs), 16),
        std::make_pair(std::make_pair(6-ofs, 7-ofs), 15),
        std::make_pair(std::make_pair(1-ofs, 8-ofs), 12),
        std::make_pair(std::make_pair(2-ofs, 8-ofs), 16),
        std::make_pair(std::make_pair(3-ofs, 8-ofs), 33),
        std::make_pair(std::make_pair(4-ofs, 8-ofs), 25),
        std::make_pair(std::make_pair(1-ofs, 9-ofs), 28),
        std::make_pair(std::make_pair(3-ofs, 9-ofs), 16),
        std::make_pair(std::make_pair(3-ofs, 10-ofs), 14),
        std::make_pair(std::make_pair(1-ofs, 11-ofs), 12),
        std::make_pair(std::make_pair(5-ofs, 11-ofs), 19),
        std::make_pair(std::make_pair(6-ofs, 11-ofs), 18),
        std::make_pair(std::make_pair(1-ofs, 12-ofs), 24),
        std::make_pair(std::make_pair(1-ofs, 13-ofs), 36),
        std::make_pair(std::make_pair(4-ofs, 13-ofs), 21),
        std::make_pair(std::make_pair(1-ofs, 14-ofs), 33),
        std::make_pair(std::make_pair(2-ofs, 14-ofs), 35),
        std::make_pair(std::make_pair(3-ofs, 14-ofs), 29),
        std::make_pair(std::make_pair(4-ofs, 14-ofs), 20),
        std::make_pair(std::make_pair(6-ofs, 17-ofs), 16),
        std::make_pair(std::make_pair(7-ofs, 17-ofs), 19),
        std::make_pair(std::make_pair(1-ofs, 18-ofs), 17),
        std::make_pair(std::make_pair(2-ofs, 18-ofs), 12),
        std::make_pair(std::make_pair(1-ofs, 20-ofs), 19),
        std::make_pair(std::make_pair(2-ofs, 20-ofs), 24),
        std::make_pair(std::make_pair(1-ofs, 22-ofs), 31),
        std::make_pair(std::make_pair(2-ofs, 22-ofs), 26),
        std::make_pair(std::make_pair(24-ofs, 26-ofs), 23),
        std::make_pair(std::make_pair(25-ofs, 26-ofs), 25),
        std::make_pair(std::make_pair(3-ofs, 28-ofs), 24),
        std::make_pair(std::make_pair(24-ofs, 28-ofs), 29),
        std::make_pair(std::make_pair(25-ofs, 28-ofs), 32),
        std::make_pair(std::make_pair(3-ofs, 29-ofs), 13),
        std::make_pair(std::make_pair(24-ofs, 30-ofs), 29),
        std::make_pair(std::make_pair(27-ofs, 30-ofs), 18),
        std::make_pair(std::make_pair(2-ofs, 31-ofs), 17),
        std::make_pair(std::make_pair(9-ofs, 31-ofs), 12),
        std::make_pair(std::make_pair(1-ofs, 32-ofs), 13),
        std::make_pair(std::make_pair(25-ofs, 32-ofs), 14),
        std::make_pair(std::make_pair(26-ofs, 32-ofs), 19),
        std::make_pair(std::make_pair(29-ofs, 32-ofs), 16),
        std::make_pair(std::make_pair(3-ofs, 33-ofs), 15),
        std::make_pair(std::make_pair(9-ofs, 33-ofs), 19),
        std::make_pair(std::make_pair(15-ofs, 33-ofs), 19),
        std::make_pair(std::make_pair(16-ofs, 33-ofs), 18),
        std::make_pair(std::make_pair(19-ofs, 33-ofs), 20),
        std::make_pair(std::make_pair(21-ofs, 33-ofs), 21),
        std::make_pair(std::make_pair(23-ofs, 33-ofs), 22),
        std::make_pair(std::make_pair(24-ofs, 33-ofs), 23),
        std::make_pair(std::make_pair(30-ofs, 33-ofs), 24),
        std::make_pair(std::make_pair(31-ofs, 33-ofs), 29),
        std::make_pair(std::make_pair(32-ofs, 33-ofs), 30),
        std::make_pair(std::make_pair(9-ofs, 34-ofs), 33),
        std::make_pair(std::make_pair(10-ofs, 34-ofs), 26),
        std::make_pair(std::make_pair(14-ofs, 34-ofs), 28),
        std::make_pair(std::make_pair(15-ofs, 34-ofs), 23),
        std::make_pair(std::make_pair(16-ofs, 34-ofs), 22),
        std::make_pair(std::make_pair(19-ofs, 34-ofs), 21),
        std::make_pair(std::make_pair(20-ofs, 34-ofs), 25),
        std::make_pair(std::make_pair(21-ofs, 34-ofs), 26),
        std::make_pair(std::make_pair(23-ofs, 34-ofs), 29),
        std::make_pair(std::make_pair(24-ofs, 34-ofs), 30),
        std::make_pair(std::make_pair(27-ofs, 34-ofs), 13),
        std::make_pair(std::make_pair(28-ofs, 34-ofs), 16),
        std::make_pair(std::make_pair(29-ofs, 34-ofs), 17),
        std::make_pair(std::make_pair(30-ofs, 34-ofs), 18),
        std::make_pair(std::make_pair(31-ofs, 34-ofs), 19),
        std::make_pair(std::make_pair(32-ofs, 34-ofs), 20),
        std::make_pair(std::make_pair(33-ofs, 34-ofs), 21.67)
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

    int64_t ofs = g.getOffset();
    if(ofs == -1) {
        // no vertices added to the graph.
        return;
    }

    std::vector < std::pair<std::pair<VertexId, VertexId>, double>> compareVec =
    {
        std::make_pair(std::make_pair(1-ofs, 2-ofs), 20),
        std::make_pair(std::make_pair(1-ofs, 3-ofs), 10),
        std::make_pair(std::make_pair(2-ofs, 3-ofs), 20),
        std::make_pair(std::make_pair(1-ofs, 4-ofs), 15),
        std::make_pair(std::make_pair(2-ofs, 4-ofs), 16),
        std::make_pair(std::make_pair(10-ofs, 15-ofs), 30),
        std::make_pair(std::make_pair(14-ofs, 15-ofs), 36)
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

    int64_t ofs = g.getOffset();
    if(ofs == -1) {
        // no vertices added to the graph.
        return;
    }   

    std::vector < std::pair<std::pair<VertexId, VertexId>, double>> compareVec =
    {
        std::make_pair(std::make_pair(1-ofs, 2-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 3-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 3-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 4-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 4-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 4-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 5-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 6-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 7-ofs), 1.0),
        std::make_pair(std::make_pair(5-ofs, 7-ofs), 1.0),
        std::make_pair(std::make_pair(6-ofs, 7-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 8-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 8-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 8-ofs), 1.0),
        std::make_pair(std::make_pair(4-ofs, 8-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 9-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 9-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 10-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 11-ofs), 1.0),
        std::make_pair(std::make_pair(5-ofs, 11-ofs), 1.0),
        std::make_pair(std::make_pair(6-ofs, 11-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 12-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 13-ofs), 1.0),
        std::make_pair(std::make_pair(4-ofs, 13-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 14-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 14-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 14-ofs), 1.0),
        std::make_pair(std::make_pair(4-ofs, 14-ofs), 1.0),
        std::make_pair(std::make_pair(6-ofs, 17-ofs), 1.0),
        std::make_pair(std::make_pair(7-ofs, 17-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 18-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 18-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 20-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 20-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 22-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 22-ofs), 1.0),
        std::make_pair(std::make_pair(24-ofs, 26-ofs), 1.0),
        std::make_pair(std::make_pair(25-ofs, 26-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 28-ofs), 1.0),
        std::make_pair(std::make_pair(24-ofs, 28-ofs), 1.0),
        std::make_pair(std::make_pair(25-ofs, 28-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 29-ofs), 1.0),
        std::make_pair(std::make_pair(24-ofs, 30-ofs), 1.0),
        std::make_pair(std::make_pair(27-ofs, 30-ofs), 1.0),
        std::make_pair(std::make_pair(2-ofs, 31-ofs), 1.0),
        std::make_pair(std::make_pair(9-ofs, 31-ofs), 1.0),
        std::make_pair(std::make_pair(1-ofs, 32-ofs), 1.0),
        std::make_pair(std::make_pair(25-ofs, 32-ofs), 1.0),
        std::make_pair(std::make_pair(26-ofs, 32-ofs), 1.0),
        std::make_pair(std::make_pair(29-ofs, 32-ofs), 1.0),
        std::make_pair(std::make_pair(3-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(9-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(15-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(16-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(19-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(21-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(23-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(24-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(30-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(31-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(32-ofs, 33-ofs), 1.0),
        std::make_pair(std::make_pair(9-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(10-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(14-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(15-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(16-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(19-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(20-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(21-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(23-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(24-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(27-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(28-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(29-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(30-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(31-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(32-ofs, 34-ofs), 1.0),
        std::make_pair(std::make_pair(33-ofs, 34-ofs), 1.0)
    };
    std::sort(compareVec.begin(), compareVec.end(), compare);
    auto vec = g.getEdgesAndWeights();
    std::sort(vec.begin(), vec.end(), compare);
    CPPUNIT_ASSERT(vec == compareVec);
}
