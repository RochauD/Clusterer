#include "TestGraphCoordinateTransformer.hpp"
#include <iostream>
CPPUNIT_TEST_SUITE_REGISTRATION(TestGraphCoordinateTransformer);

void TestGraphCoordinateTransformer::setUp(void)
{

}

void TestGraphCoordinateTransformer::tearDown(void)
{

}


void TestGraphCoordinateTransformer::printMap(const std::map<VertexId,std::pair<double,double>>& mapy)
{
    std::cout<<"\n";
    for(auto& billy : mapy){
        std::cout<<"Vertex "<<billy.first;
        std::cout<<": ("<<billy.second.first<<" , "<<billy.second.second<<")\n";
    }
}

void TestGraphCoordinateTransformer::testObtainedCoordinates(void)
{
    clb::Graph graph;

    graph.addVertex(Vertex(0));
    graph.addVertex(Vertex(1));
    graph.addVertex(Vertex(2));
    graph.addVertex(Vertex(3));
    graph.addVertex(Vertex(4));
    graph.addVertex(Vertex(5));

    // from NYC
    graph.addEdge(Vertex(0), Vertex(1), 329);
    graph.addEdge(Vertex(0), Vertex(2), 1759.93);
    graph.addEdge(Vertex(0), Vertex(3), 1145.58);
    graph.addEdge(Vertex(0), Vertex(4), 4133.71);
    graph.addEdge(Vertex(0), Vertex(5), 7990.70);

    graph.addEdge(Vertex(1), Vertex(0), 329);
    graph.addEdge(Vertex(2), Vertex(0), 1759.93);
    graph.addEdge(Vertex(3), Vertex(0), 1145.58);
    graph.addEdge(Vertex(4), Vertex(0), 4133.71);
    graph.addEdge(Vertex(5), Vertex(0), 7990.70);  

    // from Washingon DC
    graph.addEdge(Vertex(1), Vertex(2), 1492.85);
    graph.addEdge(Vertex(1), Vertex(3), 956.26);
    graph.addEdge(Vertex(1), Vertex(4), 3922.93);
    graph.addEdge(Vertex(1), Vertex(5), 7779.88);

    graph.addEdge(Vertex(2), Vertex(1), 1492.85);
    graph.addEdge(Vertex(3), Vertex(1), 956.26);
    graph.addEdge(Vertex(4), Vertex(1), 3922.93);
    graph.addEdge(Vertex(5), Vertex(1), 7779.88);

    // from Miami
    graph.addEdge(Vertex(2), Vertex(3), 1919.46);
    graph.addEdge(Vertex(2), Vertex(4), 4174.43);
    graph.addEdge(Vertex(2), Vertex(5), 7825.37);

    graph.addEdge(Vertex(3), Vertex(2), 1919.46);
    graph.addEdge(Vertex(4), Vertex(2), 4174.43);
    graph.addEdge(Vertex(5), Vertex(2), 7825.37);

    // from Chicago
    graph.addEdge(Vertex(3), Vertex(4), 2988.24);
    graph.addEdge(Vertex(3), Vertex(5), 6845.75);

    graph.addEdge(Vertex(4), Vertex(3), 2988.24);
    graph.addEdge(Vertex(5), Vertex(3), 6845.75);

    // from San Francisco 
    graph.addEdge(Vertex(4), Vertex(5), 3858.23);
    graph.addEdge(Vertex(5), Vertex(4), 3858.23);

    GraphCoordinateTransformer tr(graph);
    std::map<VertexId,std::pair<double,double>> map;
    map = tr.getCoordinateMap();
    printMap(map);
    
    // default offset is 5
    map = tr.getNormalizedMap(400,500);
    printMap(map);


    // the coordinates look as they should, jugding from the picture
    // provided
    // a bit difficult to come up with a concrete test, for now...

    CPPUNIT_ASSERT(false);
}