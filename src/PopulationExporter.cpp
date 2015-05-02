/**
 * @file PopulationExporter.cpp
 * @brief Export population to file.
 */

#include "../include/PopulationExporter.hpp"
#include "../include/GlobalFileLogger.hpp"
// standard headers
// external headers

// internal headers

namespace clusterer
{

namespace backend
{
bool PopulationExporter::WritePopulationToFile(std::vector<std::pair<Encoding, double>>* p, std::string fullPathName)
{
    std::ofstream file(fullPathName);
    //
    for (auto& e: *p)
    {
	// print structure to be formatted:
	if(!(file<<'\n'<<e.second<<'\n'))
	{
	    clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting endocoding information.");
	    return false;
	}
	
	for (auto& f: e.first)
	{
	    if(!(file<<f<<" "))
	    {
		clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting endocoding information.");
		return false;
	    }
	}
	
	file<<'\n';	
    }
    
    if (file.bad() || file.fail())
    {
	clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Failed exporting population.");
	return false;
    }
    return true;
}

}    

}
