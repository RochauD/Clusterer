/**
  * @file GeneticGui.hpp
  * @brief file containing the singleton for the genetic application
  */
#ifndef _FRONTEND_GENETICGUI_HPP
#define _FRONTEND_GENETICGUI_HPP

namespace frontend {

/**
 * @class GeneticGui
 * @brief Singleton for the Qt frontend of social clustering
 * */
class GeneticGui{
 public:
    /**
      * @brief configuration to decide how to display data
      */
    struct Config {
        char clusterDisplayMode;
        bool displayFitnessPlot;
    };

    /**
     * @brief get the singleton instance
     */
    static GeneticGui& getApp() {
        static GeneticGui app;
        return app;
    }

    /**
     * @brief set configuration parameters
     * @param config the configuration to be installed
     */
    void setConfigParams(const Config& config);
    /**
     * @brief get the configuration parameters
     */
    Config getConfigParams() const;

    /*
     * @brief start the GUI instance in its own thread
     */
    void startGui(void);
        
 private:
    /** 
     * @brief constructor which registers a particular config
     * @param config the configuration of this query handler
     */
    GeneticGui();
    /**
     * @brief standard destructor
     */
    ~FrontendQHandler() {}
    /**
     * @brief copy constructor
     */
    GeneticGui(const GeneticGui&);

    /**
     * @brief config used when displaying information
     */
    const Config& _config;
};

}  // namespace frontend

#endif  // _FRONTEND_GENETICGUI_HPP

