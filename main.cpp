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
#include "include/ClusteringPopulationAnalyzer.hpp"
#include "include/IntegerEncodingInitializer.hpp"
#include "include/IntegerVectorEncoding.hpp"
#include "include/FitnessAnalyzer.hpp"
#include "include/TwoPhaseStrategy.hpp"
#include "include/ConcurrentLockingQueue.hpp"

using namespace clc;
using namespace clb;

int main()
{
    GlobalFileLogger::init();
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Exe Version: ", CLUSTERER_VERSION);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Exe Version FUll: ", CLUSTERER_VERSION_FULL);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Lib Version: ", CLUSTERER_LIB_VERSION);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Lib Version FUll: ", CLUSTERER_LIB_VERSION_FULL);

    Graph graph;
    // Initialize graph 2
    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));
    graph.addVertex(Vertex(5));
    graph.addVertex(Vertex(6));
    graph.addVertex(Vertex(7));

    graph.addEdge(Vertex(0), Vertex(1), 0.2);
    graph.addEdge(Vertex(1), Vertex(2), 0.3);
    graph.addEdge(Vertex(1), Vertex(3), 0.5);
    graph.addEdge(Vertex(2), Vertex(3), 0.4);
    graph.addEdge(Vertex(3), Vertex(4), 0.2);
    graph.addEdge(Vertex(4), Vertex(5), 0.5);
    graph.addEdge(Vertex(4), Vertex(6), 0.6);
    graph.addEdge(Vertex(5), Vertex(6), 0.7);
    graph.addEdge(Vertex(6), Vertex(7), 0.1);

    ConfigurationManager cfg;
    cfg.saveClusteringParams("config.cfg");
    cfg.loadClusteringParams("config2.cfg");

    ConcurrentLockingQueue<std::pair<IntegerVectorEncoding, double>> outQueue;
    std::vector<std::pair<IntegerVectorEncoding, double>> population;

    TwoPhaseStrategy<IntegerVectorEncoding, IntegerEncodingInitializer> algorithmService(&graph, cfg.getClusteringParams(), &population, &outQueue);
    algorithmService.runAlgorithm();





    /*
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
    */


    return 0;
}

