/**
* @file PopulationImporter.cpp
* @brief Imports a population from a file.
*/

#include "../include/PopulationImporter.hpp"

// standard headers
#include <string>
#include <sstream>
// external headers

// internal headers
#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{

namespace backend
{

PopulationImporter::PopulationImporter()
{

}

PopulationImporter::~PopulationImporter()
{

}

bool PopulationImporter::loadPopulationFromFile(std::string fullPathName, AbstractGraph* graph, std::vector<PopulationMember<IntegerVectorEncoding, double>>* population)
{
    if (population == nullptr || graph == nullptr)
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed importing population, because a null pointer was passed to the function. Tried to read from file: ", fullPathName);
        return false;
    }
    population->resize(0); // clear population

    std::ifstream file(fullPathName);
    if (file.fail())
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Cannot open file: ", fullPathName);
        return false;
    }
    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            PopulationMember<IntegerVectorEncoding, double> member;
            member.modified = true;
            IntegerVectorEncoding encoding(graph);
            std::string buffer;

            // read in fitness
            std::istringstream iss(line);
            iss >> member.fitnessValue;
            // read in cluster encoding
            if (std::getline(file, buffer))
            {
                size_t i = 0;
                std::istringstream ss(buffer);
                uint64_t val;
                while (ss >> val)
                {
                    if (encoding.addToCluster(i, val) == -1)
                    {
                        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Invalid formatting of population file: ", fullPathName);
                        return false;
                    }
                    i++;
                }
            }
            else
            {
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Invalid formatting of population file: ", fullPathName);
                return false;
            }
            if (encoding.normalize() == -1)
            {
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not normalize population member. Population file: ", fullPathName);
                return false;
            }
            member.populationEncoding = encoding;
            population->push_back(member);
        }
        file.close();
    }

    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Succesfully imported population from the file: ", fullPathName);
    return true;
}

}
}
