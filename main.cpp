#include <iostream>
#include <cstdlib>
#include <iostream>
#include <memory>
#include "include/Vertex.hpp"
#include "include/AbstractGraph.hpp"
#include "include/Graph.hpp"
#include "include/GraphReader.hpp"
#include "include/Logger.hpp"
#include "include/LoggingPolicyFile.hpp"
#include "include/ConfigurationManager.hpp"
#include "include/GlobalFileLogger.hpp"

using namespace clc;
using namespace clb;

int main()
{

    std::unique_ptr<LoggingPolicyFile> uPtr(new LoggingPolicyFile("./", "test"));
    Logger<LoggingPolicyFile> logger(std::move(uPtr), SeverityLevel::ALL);
    GlobalFileLogger::init();

    for (size_t i = 0; i < 100; i++)
    {
        logger.log(SeverityType::INFO, "Info: ", i);
        GlobalFileLogger::instance()->log(SeverityType::DEBUG, "test", i);
    }

    Graph g;
    GraphReader gr(&g);
    gr.readFile("../test_files/out.ucidata-zachary");
    // can be replaced with "test_files/out.ucidata-zachary"

    std::cout << "number of edges: " << g.getNoEdges() << "\n";
    std::cout << "number of vertices: " << g.getNoVertices() << "\n";

    std::vector<std::pair<VertexId, VertexId>> edges = g.getEdges();

    std::cout << "edges: \n";
    std::vector<std::pair<VertexId, VertexId>>::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it)
    {
        std::cout << (*it).first << " " << (*it).second << "\n";
    }

    std::cout << "vertices: \n";
    std::vector<VertexId> vec = g.getVertices();

    std::vector<VertexId>::iterator it2;
    for (auto t : vec)
    {
        std::cout << t << " ";
    }
    std::cout << "\n";

    std::vector<std::pair<std::pair<VertexId, VertexId>, double>> wedges = g.getEdgesAndWeights();

    std::cout << "edges: \n";
    std::vector<std::pair<std::pair<VertexId, VertexId>, double>>::iterator wit;
    for (wit = wedges.begin(); wit != wedges.end(); ++wit)
    {
        std::cout << (*wit).first.first << " " << (*wit).first.second;
        std::cout << " with weight: " << (*wit).second << "\n";
    }


    logger.log(SeverityType::WARNING, "File: ", __FILE__);
    logger.log(SeverityType::WARNING, "Definition Exe Version: ", (CLUSTERER_VERSION));
    logger.log(SeverityType::WARNING, "Definition Exe Version FUll: ", CLUSTERER_VERSION_FULL);

    logger.log(SeverityType::WARNING, "Definition Lib Version: ", CLUSTERER_LIB_VERSION);
    logger.log(SeverityType::WARNING, "Definition Lib Version FUll: ", CLUSTERER_LIB_VERSION_FULL);

    ConfigurationManager cfg;
    cfg.saveClusteringParams("config1.txt");
    cfg.setMaxFitness(11235467889.000);
    cfg.saveClusteringParams("config2.txt");
    cfg.loadClusteringParams("config2.txt");

    return 0;
}

