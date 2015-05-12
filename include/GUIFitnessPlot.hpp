
/**
 * @file GUIFitnessPlot.hpp
 * @brief class to plot the fitness over time
 */

#ifndef CLUSTERER_FRONTEND_GUIPLOTFITNESS_HPP_INCLUDED
#define CLUSTERER_FRONTEND_GUIPLOTFITNESS_HPP_INCLUDED

// standard headers
#include <stdint.h>
#include <atomic>
#include <mutex>
#include <chrono>
#include <random>
#include <vector>
#include <QTimer>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_zoomer.h>
#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_series_data.h>
#ifdef _WIN32
#include <qwt_legend.h>
#else
#include <qwt/qwt_legend.h>
#endif

// internal headers
#ifndef Q_MOC_RUN
#include "ClusteringService.hpp"
#include "GlobalBackendController.hpp"
#include "ConcurrentLockingQueue.hpp"
#endif

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace frontend
* @brief The namespace frontend is the namespace for all front end components of the
* project.
*/
namespace frontend
{

/**
 * @class GUIFitnessPlot.hpp
 * @brief A widget to plot the change in fitness over time
 */
class GUIFitnessPlot: public QWidget
{
        Q_OBJECT

    public:
        /**
        * @brief constructor which takes the graph and gets the normalized coordinates from the MDS
        * implemented by GraphCoordinateTransformer class.
        * @param parent widget if applicable
        */
        GUIFitnessPlot(QWidget* parent, uint64_t width = 400, uint64_t height = 400);

        /**
        * @brief empty destructor
        */
        ~GUIFitnessPlot();

        /**
         * @brief Update the plot with new fitness values
         * @param vector A vector of <x, y> data points
         */
        void replotFitness(std::vector<std::pair<uint64_t, double>> vector);
    private:
        /* myPlot is put inside plotWindow*/
        QWidget* plotWindow;
        QwtPlot* myPlot;

        QwtPlotCurve* curve;
        QwtPlotZoomer* zoom;
        QwtPointSeriesData* fitness_data;
        QVector<QPointF>* samples;

        /**
        * @brief setting the background of the plot
        */
        void setPlotBackground();

        /**
        * @brief private slot for drawing the content of the supplied coordinates
        * if a "plot" button is pushed
        */
        void plotContent();
};

}
}

#endif
