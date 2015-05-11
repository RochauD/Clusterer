
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
#include <QMainWindow>
#include <QTimer>
#include <QtGui>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_zoomer.h>
#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_series_data.h>
#include <qwt/qwt_legend.h>

// internal headers
#include "ClusteringService.hpp"
#include "GlobalBackendController.hpp"
#include "ConcurrentLockingQueue.hpp"

class QWindow;
class QPushButton;
class QMessageBox;

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

class GUIFitnessPlot: public QMainWindow
{
    Q_OBJECT

    public:
        /**
        * @brief constructor which takes the graph and gets the normalized coordinates from the MDS
        * implemented by GraphCoordinateTransformer class.
        * @param parent widget if applicable
        */
        GUIFitnessPlot(QWidget *parent, uint64_t width = 400, uint64_t height = 400);
        
        /**
        * @brief empty destructor
        */
        ~GUIFitnessPlot();

    public slots:
        void replotFitness(double);

    private slots:
        void genRandomValues();

    signals:
        void sendFitnessValue(double);

    private:
        /* general purpose buttons */
        QPushButton *closeFit;

        /* central widget to rule them all */
        QWidget *central_vis_window;
        int counter;
        /* myPlot is put inside plotWindow*/
        QWidget *plotWindow;
        QwtPlot *myPlot;

        QwtPlotCurve *curve;
        QwtPlotZoomer *zoom;
        QwtPointSeriesData *fitness_data;
        QVector<QPointF> *samples;
        
        QTimer *timer;
        std::mutex lockFit;

        /* random generator to generate random symbols for the clusters
        when GUIFitnessPlot object is created */
        std::mt19937 *gen;
        std::uniform_real_distribution<double> dist;

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

#endif // GUIFITNESSPLOT_HPP_INCLUDED