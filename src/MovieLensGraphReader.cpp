/**
* @file MovieLensGraphReader.cpp
* @brief Implementation of MovieLensGraphReader
*/

// standard headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <set>
// external headers

// internal headers
#include "../include/MovieLensGraphReader.hpp"
#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{
namespace backend
{

size_t findRating(size_t userID, size_t movieID, std::unordered_map<size_t, std::set<std::pair<size_t, size_t>>>& dataMap)
{
    for (auto& e : dataMap[userID])
    {
        if (e.first == movieID)
        {
            return e.second;
        }
    }
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not find rating for movie with id: ", movieID, " for user: ", userID);
    throw std::runtime_error("Could not find rating!");
}

/**
* @param A One of the two vertices of the edge whose weight will be computed.
* @param B One of the two vertices of the edge whose weight will be computed.
* @return Weight of the edge.
*/
float computeWeight(size_t A, size_t B, std::unordered_map<size_t, std::set<std::pair<size_t, size_t>>>& dataMap)
{
    std::vector<std::pair<size_t, size_t>> intersectionofAandB;

    // find set of movies rated by both A and B
    std::set_intersection(dataMap[A].begin(), dataMap[A].end(), dataMap[B].begin(), dataMap[B].end(), std::back_inserter(intersectionofAandB),
                          [=](const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b)->bool
    {
        return a.first < b.first;
    });

    if (intersectionofAandB.size() == 0)
    {
        return 0.0;
    }

    // Read each line, check if it is intersection, then compute the similarity.
    unsigned long long sumofsquaredrating = 0;
    for (auto iter = intersectionofAandB.begin(); iter != intersectionofAandB.end(); iter++)
    {
        auto result = findRating(A, iter->first, dataMap) - findRating(B, iter->first, dataMap);
        sumofsquaredrating += result*result;
    }

    double similarity = sumofsquaredrating / intersectionofAandB.size();
    return (1.0 / (1.0 + sqrt(similarity)));
}

MovieLensGraphReader::MovieLensGraphReader(AbstractGraph* graph) : AbstractGraphReader(graph)
{

}

MovieLensGraphReader::~MovieLensGraphReader()
{

}

bool MovieLensGraphReader::readFile(std::string fullPathName)
{
    std::ifstream file(fullPathName, std::ios::in);

    if (file.fail())
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Cannot open file: ", fullPathName);
        return false;
    }

    std::unordered_map<size_t, std::set<std::pair<size_t, size_t>>> dataMap;
    std::set<size_t> userSet;

    std::string line;
    size_t lineNumber = 0;
    size_t userID;
    size_t itemID;
    size_t rating;
    size_t timestamp;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            if (iss >> userID >> itemID >> rating >> timestamp)
            {
                dataMap[userID].insert(std::make_pair(itemID, rating));
                userSet.insert(userID);
            }
            else
            {
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Invalid formatting in file: ", fullPathName, " at line ", lineNumber);
                return false;
            }
            lineNumber++;
        }
        file.close();
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not open file: ", fullPathName);
    }

    std::vector<size_t> userVec(userSet.begin(), userSet.end());
    for (size_t i = 0; i < userVec.size(); i++)
    {
        for (size_t j = 0; j < userVec.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                auto weight = computeWeight(userVec[i], userVec[j], dataMap);
                if (weight > 0.0001)
                {
                    this->graph->addEdge(Vertex(userVec[i]), Vertex(userVec[j]), weight);
                }
            }
        }
    }

    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Read the following file containing a graph succesfully. File: ", fullPathName);
    return true;
}

}
}
