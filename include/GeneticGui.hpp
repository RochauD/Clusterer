/**
 * @file GeneticGui.hpp
 * @brief file containing the singleton for the genetic application
 */
#ifndef CLUSTERER_FRONTEND_GENETIC_GUI_HPP
#define CLUSTERER_FRONTEND_GENETIC_GUI_HPP

// standard headers

// external headers

// internal headers


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
 * @class GeneticGui
 * @brief Singleton for the Qt frontend of social clustering
 * */
class GeneticGui
{
    public:
        /**
          * @brief configuration to decide how to display data
          */
        struct Config
        {
            char clusterDisplayMode;
            bool displayFitnessPlot;
        };

        /**
         * @brief get the singleton instance
         */
        static GeneticGui& getApp()
        {
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
        const Config getConfigParams();

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
        ~GeneticGui() {}
        /**
         * @brief copy constructor
         */
        GeneticGui(const GeneticGui&);

        /**
         * @brief config used when displaying information
         */
        Config _config;
};

}
}

/**
* @namespace clf
* @brief The namespace clc is a namespace alias for the namespace clusterer::common.
*/
namespace clf = clusterer::frontend;

#endif

