/**
 * @file GeneticGui.hpp
 * @brief file containing the singleton for the genetic application
 */
#ifndef CLUSTERER_FRONTEND_GENETIC_GUI_HPP
#define CLUSTERER_FRONTEND_GENETIC_GUI_HPP

// standard headers

// external headers
#include <QWidget>
#include <QStatusBar>

// internal headers
#include "ClustererMenuBar.hpp"
#include "ClustererWindow.hpp"

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
         * @brief get the singleton instance
         */
        static GeneticGui& getApp()
        {
            static GeneticGui app;
            return app;
        }

        /*
         * @brief start the GUI instance in its own thread
         */
        void startGui(void);



    private:
        ClustererWindow window;
        ClustererMenuBar* menuBar;

        /**
         * @brief The default constructor sets up the main window
         */
        GeneticGui();
        /**
         * @brief standard destructor
         */
        ~GeneticGui() {}
        /**
         * @brief copy constructor
         */
        GeneticGui(const GeneticGui&) = delete;
        /**
         * @brief assignment operator
         */
        void operator=(GeneticGui const&) = delete;
};

}
}

/**
* @namespace clf
* @brief The namespace clc is a namespace alias for the namespace clusterer::frontend.
*/
namespace clf = clusterer::frontend;

#endif

