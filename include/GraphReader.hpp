/**
*@file GraphReader.h
*@brief File in which GraphReader class is defined
*/
#ifndef GRAPHREADER_H_INCLUDED
#define GRAPHREADER_H_INCLUDED
#include <string>
#include <vector>
#include <stdint.h>

/**
*@class GraphReader
*@brief Reads the edges of the graph and their weights from the given file
*/

class GraphReader
{

    public:

    /**
    *@brief constructor with  a parameter
    *@param filename, name of the file containing the data
    */
    GraphReader(std::string filename);

    /**
    *@brief Default destructor for GraphReader
    */
    ~GraphReader();

    /**
    *@brief setter method for filename
    *@param filename, name of the file containing the data
    *@return void
    */
    void setFilename(std::string filename);

    /**
    *@brief getter method for filename
    *@return returns the name of the file containing the data
    */
    std::string getFilename();

    /**
    *@brief method for reading file and setting the Edges and EdgesWeight properties of an object.
    *@return uint64_t
    */
    uint64_t readFile();


    /**
    *@brief method for getting the Edges property.
    *@return vector containing the edges of the graph with the start and end nodes
    */
    std::vector<std::pair<uint64_t,uint64_t> >getEdges();

    /**
    *@brief method for printing the edges
    *@param graphEdges, vector containing the edges of the graph with the start and end nodes
    *@return void
    */
    void printEdges(std::vector<std::pair<uint64_t,uint64_t> > graphEdges);


    /**
    *@brief method for getting the EdgesWeight property of an object
    *@return vector containing the edges with the start and end nodes and their corresponding weight
    */
    std::vector<std::pair<std::pair<uint64_t,uint64_t>, uint64_t > > getEdgesWeight();

    /**
    *@brief method for printing the edges with weight.
    *@param graphEdgesWeight, vector containing the edges with the start and end nodes and their corresponding weight
    *@return void
    */
    void printEdgesWeight(std::vector<std::pair<std::pair<uint64_t,uint64_t>, uint64_t > >graphEdgesWeight);

    /**
    *@brief method for getting the  vertices.
    *@return vector<uint64_t>
    */
    std::vector<uint64_t> getVertices();

    /**
    *@brief method for printing the vertices
    *@param graphVertices, vector containing the vertices
    *@return void
    */
    void printVertices(std::vector<uint64_t> graphVertices);

    /**
    *@brief method for getting the total number of vertices.
    *@return uint64_t
    */
    uint64_t getVerticesCount();

    /**
    *@brief method for getting the total number of edges.
    *@return uint64_t
    */
    uint64_t getEdgesCount();

    private:
    /**
    * @var vertices
    * @brief vector containing the vertices
    * @var edges
    * @brief vector containing the edges with the start and end nodes
    * @var edgesWeight
    * @brief vector containing the edges with the start and end nodes and their corresponding weight
    * @var filename
    * @brief name of the file containing the data
    * @var verticesCount
    * @brief total number of vertices
    * @var edgesCount
    * @brief total number of edges
    */

    std::vector<uint64_t> vertices;
    std::vector<std::pair<uint64_t, uint64_t> > edges;
    std::vector<std::pair<std::pair<uint64_t,uint64_t>, uint64_t > >edgesWeight;
    std::string filename;
    uint64_t verticesCount;
    uint64_t edgesCount;

};

#endif // GRAPHREADER_H_INCLUDED



