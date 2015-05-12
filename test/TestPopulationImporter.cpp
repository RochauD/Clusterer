#include "TestPopulationImporter.hpp"
#include "../include/AbstractGraph.hpp"
#include "../include/Graph.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/ClusterEncoding.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TestPopulationImporter);

bool equalImporter(std::vector<PopulationMember<IntegerVectorEncoding, double>>& p1, std::vector<PopulationMember<IntegerVectorEncoding, double>>& p2)
{
    if (p1.size() != p2.size())
    {
        return false;
    }

    for (size_t i = 0; i < p1.size(); i++)
    {
        if (p1[i].fitnessValue != p2[i].fitnessValue)
        {
            return false;
        }
        auto vec1 = p1[i].populationEncoding.getEncoding();
        auto vec2 = p2[i].populationEncoding.getEncoding();

        std::sort(vec1.begin(), vec1.begin());
        std::sort(vec2.begin(), vec2.end());

        if (vec1 != vec2)
        {
            return false;
        }
    }
    return true;
}


void TestPopulationImporter::setUp(void)
{

}

void TestPopulationImporter::tearDown(void)
{

}

void TestPopulationImporter::testLoadPopulationFromFile(void)
{
    Graph g;
    g.addEdge(Vertex(0),Vertex(1),0.2);
    g.addEdge(Vertex(1),Vertex(2),0.3);
    g.addEdge(Vertex(1),Vertex(3),0.4);
    g.addEdge(Vertex(3),Vertex(4),0.5);
    g.addEdge(Vertex(4),Vertex(5),0.6);
    g.addEdge(Vertex(4),Vertex(6),0.7);

    // create a population
    std::vector<PopulationMember<IntegerVectorEncoding, double>> population1;
    IntegerVectorEncoding code1(&g);
    code1.addToCluster(0,0);
    code1.addToCluster(1,0);
    code1.addToCluster(2,0);
    code1.addToCluster(3,0);
    code1.addToCluster(4,1);
    code1.addToCluster(5,1);
    code1.addToCluster(6,1);
    const IntegerVectorEncoding code12=code1;
    PopulationMember<IntegerVectorEncoding, double> mem;
    mem.fitnessValue = 1.48;
    mem.populationEncoding = code12;
    population1.push_back(mem);

    IntegerVectorEncoding code2(&g);
    code2.addToCluster(0,0);
    code2.addToCluster(1,0);
    code2.addToCluster(2,1);
    code2.addToCluster(3,1);
    code2.addToCluster(4,1);
    code2.addToCluster(5,2);
    code2.addToCluster(6,2);
    const IntegerVectorEncoding code22=code2;
    mem.fitnessValue = 1.14;
    mem.populationEncoding = code22;
    population1.push_back(mem);

    // write population to file

    std::ofstream file("testPopulationImporter.txt");

    for (auto& ele : population1)
    {
        file << ele.fitnessValue << '\n';
        for (auto& f : ele.populationEncoding.getEncoding())
        {
            file << f << " ";
        }
        file << '\n';
    }
    file.close();

    PopulationImporter importer;
    std::vector<PopulationMember<IntegerVectorEncoding, double>> population2;
    importer.loadPopulationFromFile("testPopulationImporter.txt",&g,&population2);
    bool assert=equalImporter(population1,population2);
    CPPUNIT_ASSERT(assert);

}
