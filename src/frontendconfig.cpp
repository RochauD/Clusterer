#include "../include/frontendconfig.h"

bool FrontendConfig::visualizeGraph;

void FrontendConfig::setVisualizeGraph(bool val)
{
    visualizeGraph = val;
}

bool FrontendConfig::getVisualizeGraph()
{
    return visualizeGraph;
}
