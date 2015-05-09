/**
 * @file PopulationExporter.cpp
 * @brief Export population to file.
 */

#include "../include/PopulationExporter.hpp"

// standard headers

// external headers

// internal headers
#include "../include/GlobalFileLogger.hpp"

namespace clusterer
{

namespace backend
{

PopulationExporter::PopulationExporter()
{

}

PopulationExporter::~PopulationExporter()
{

}

bool PopulationExporter::writePopulationToFile(std::vector<PopulationMember<IntegerVectorEncoding, double>>* population, std::string fullPathName)
{
    std::ofstream file(fullPathName);
    for (auto& ele : *population)
    {
        // print structure to be formatted:
        if (!(file << ele.fitnessValue << '\n'))
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting population information. Tried to write into file: ", fullPathName);
            return false;
        }

        for (auto& f : ele.populationEncoding.getEncoding())
        {
            if (!(file << f << " "))
            {
                clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting population information. Tried to write into file: ", fullPathName);
                return false;
            }
        }
        file << '\n';
    }

    if (file.bad() || file.fail())
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting population information. Tried to write into file: ", fullPathName);
        return false;
    }
    file.close();
    clc::GlobalFileLogger::instance()->log(clc::SeverityType::INFO, "Succesfully exported population into file: ", fullPathName);
    return true;
}

}
}
