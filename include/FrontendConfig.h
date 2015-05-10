/**
 * @file FrontendConfig.h
 * @brief Static class containing the configuration for the frontend
 */
#ifndef FRONTENDCONFIG_H
#define FRONTENDCONFIG_H

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace frontend
* @brief The namespace frontend is the namespace for all frontend components of the
* project.
*/
namespace frontend
{

/**
 * @class FrontendConfig.h
 * @brief Static class containing the configuration for the frontend
 */
class FrontendConfig
{
public:
    /**
     * @brief Setter for visualizeGraph
     * @arg The new value for the variable
     */
    static void setVisualizeGraph(bool val);
    /**
     * @brief Getter for vizualizeGraph
     * @return The visualizeGraph variable
     */
    static bool getVisualizeGraph();

private:
    static bool visualizeGraph;
};

}
}
#endif // FRONTENDCONFIG_H
