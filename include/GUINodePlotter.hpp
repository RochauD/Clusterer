
/**
 * @file GUINodePlotter.hpp
 * @brief class to visually plot the result of implementation of a transformer to obtain
 *  coordinates for a graph's nodes using the edge's weights
 */

#ifndef CLUSTERER_FRONTEND_GUINODEPLOTTER_HPP_INCLUDED
#define CLUSTERER_FRONTEND_GUINODEPLOTTER_HPP_INCLUDED

 // standard headers
#include <stdint.h>
#include <atomic>
#include <mutex>
#include <map>
//#include <vector>
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
#include <qwt_math.h>
#include <qwt_symbol.h>
#include <qwt_series_data.h>
#include <qwt/qwt_legend.h>

// internal headers
#ifndef Q_MOC_RUN
#include "ClusterEncoding.hpp"
#include "IntegerVectorEncoding.hpp"
#include "AbstractGraph.hpp"
#include "Graph.hpp"
#include "ClusteringService.hpp"
#include "GlobalBackendController.hpp"
#include "GraphCoordinateTransformer.hpp"
#include "ConcurrentLockingQueue.hpp"
#endif
 
class QWindow;
class QLabel;
class QDialog;
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

class GUINodePlotter: public QWidget
{
    Q_OBJECT

    public:
        /**
        * @brief constructor which takes the graph and gets the normalized coordinates from the MDS
        * implemented by GraphCoordinateTransformer class.
        * @param parent widget if applicable
        * @param width value
        * @param height value
        */
        GUINodePlotter(QWidget *parent, uint64_t width = 500, uint64_t height = 500);

        void initGraph();
        
        /**
        * @brief empty destructor
        */
        ~GUINodePlotter();

    public slots:
        /**
        * @brief redraw solution based on supplied solution
        * @param a ClusterEncoding object
        */  
        void replotSolution(backend::ClusterEncoding& clusterSol);

        /**
        * @bried draw edges for the graph
        * @param graph object
        */
        void draw_edges();

        /* uncomment next 2 for auto generating solutions */
        //void genSolution(backend::ClusterEncoding& clusterSol);
        //void genSol2();

    private slots:

    signals:
        void sendSol(backend::ClusterEncoding& clusterSol);
        void drawEdges();

    private:
        /* general purpose buttons */
        QPushButton *show_edges;
        QPushButton *closeViz;

        int width = 500;
        int height = 500;

        /* central widget to rule them all */
        // QWidget *central_vis_window;
        int counter;
        /* myPlot is put inside plotWindow*/
        QWidget *plotWindow;
        QwtPlot *myPlot;

        QwtPlotCurve *curve;
        QVector<QwtPlotMarker*> markers;
        QwtPlotZoomer *zoom;
        QwtPointSeriesData *mydata;

        QVector<QwtSymbol*> *symbols;
        QVector<QColor> *colors;
        QVector<QPointF> *samples;
        
        QTimer *timer;
        std::mutex lock;

        /* random generator to generate random symbols for the clusters
        when GUINodePlotter object is created */
        std::mt19937 *gen;
        std::uniform_int_distribution<int> dist;

        /**
        * @brief storing the supplied map for local use
        */
        std::map<backend::VertexId,std::pair<double,double>> mapy;
        /**
        * @brief just for testing
        */
        void printMap(const std::map<backend::VertexId,std::pair<double,double>>&);
        void printEncoding(const backend::ClusterEncoding& clusterSol);
        /**
        * @brief setting the background of the plot
        */
        void setPlotBackground(const uint64_t& width, const uint64_t& height);
        /**
        * @brief set symbols for plotting the solution's clusters
        */
        void setSymbols(uint64_t no_vertices);

        /**
        * @brief private slot for drawing the content of the supplied coordinates
        * if a "plot" button is pushed
        */   
        void plotContent();

        backend::IntegerVectorEncoding solution;
        backend::ClusteringService *_service;
        
};

}
}

#endif // GUINODEPLOTTER_HPP_INCLUDED