/**
 * @file GraphExporter.cpp
 * @brief Export graph to files.
 */

#include "../include/GraphExporter.hpp"
#include "../include/GlobalFileLogger.hpp"
// standard headers
#include <string>
// external headers

// internal headers

namespace clusterer
{

namespace backend
{

bool GraphExporter::WriteGraphToFile(AbstractGraph* g,std::string fullPathName)
{
    std::ofstream file(fullPathName);
    std::vector<std::pair<std::pair<VertexId,VertexId>,double>> edgesAndWeights=g->getEdgesAndWeights();
    for (auto& e:edgesAndWeights)
    {
        if (!(file << (e.first).first << " " << (e.first).second << " " << e.second << '\n'))
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting graph into file ", fullPathName);
            return false;
        }
    }
    if (file.bad() || file.fail())
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting graph into file " , fullPathName);
        return false;
    }
    file.close();
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Succesfully exported graph into file " , fullPathName);
    return true;
}

}
}
