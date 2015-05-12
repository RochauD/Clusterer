#ifndef FRONTENDCONFIG_H
#define FRONTENDCONFIG_H


class FrontendConfig
{
public:
    static void setVisualizeGraph(bool val);
    static bool getVisualizeGraph();

private:
    static bool visualizeGraph;
};

#endif // FRONTENDCONFIG_H
