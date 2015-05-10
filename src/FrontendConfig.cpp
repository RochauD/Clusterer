/**
 * @file FrontendConfig.h
 * @brief Static class containing the configuration for the frontend
 */

#include "../include/FrontendConfig.h"

namespace clusterer
{

namespace frontend
{


bool FrontendConfig::visualizeGraph;

void FrontendConfig::setVisualizeGraph(bool val)
{
    visualizeGraph = val;
}

bool FrontendConfig::getVisualizeGraph()
{
    return visualizeGraph;
}

}
}
