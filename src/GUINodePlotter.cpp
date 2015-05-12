/**
* @file GUINodePlotter.cpp
* @brief class to visually plot the result of implementation of a transformer to obtain
*  coordinates for a graph's nodes using the edge's weights
*/

#include <iostream>
#include "../include/GUINodePlotter.hpp"

namespace clusterer
{
namespace frontend
{

GUINodePlotter::GUINodePlotter(QWidget* parent, uint64_t Width, uint64_t Height)
    : QWidget(parent),width(Width),height(Height)
{
    /* resizing window */
    this->resize(Width,Height);
    this->adjustSize();
    /*creating the necessary widgets*/

    plotWindow = new QWidget();

    /* setting the default background for the plot */
    setPlotBackground(Width,Height);

    /* add myPlot to plotWindow */
    QVBoxLayout* layout_t = new QVBoxLayout();
    layout_t->addWidget(myPlot);

    plotWindow->setLayout(layout_t);
    plotWindow->setWindowModality(Qt::ApplicationModal);
    plotWindow->show();

    /* add zooming option */
    zoom = new QwtPlotZoomer(myPlot->canvas());
    zoom->setRubberBandPen(QPen(Qt::black, 2, Qt::DotLine));
    zoom->setTrackerPen(QPen(Qt::black));

    /*setting the layout of the main window*/
    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    layout2->addLayout(layout1);
    layout2->addWidget(plotWindow);
    this->setLayout(layout2);

    /* generate symbols for the clusters */
    /* obtain a seed from the system clock: */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = new std::mt19937(seed);
    dist = std::uniform_int_distribution<int>(0,255);

    connect(this,SIGNAL(sendSol(backend::ClusterEncoding&)),
            this,SLOT(replotSolution(backend::ClusterEncoding&)),Qt::DirectConnection);
    connect(this,SIGNAL(drawEdges()),this,SLOT(draw_edges()));

}


void GUINodePlotter::initGraph()
{
    //clearGraph();

    GraphCoordinateTransformer gt(clb::GlobalBackendController::instance()->getGraph());
    mapy = gt.getNormalizedMap(this->width,this->height);
    plotContent();

    myPlot->replot();
    //myPlot->show();
    setSymbols(clb::GlobalBackendController::instance()->getGraph().getNoVertices());
}

void GUINodePlotter::setSymbols(uint64_t no_vertices)
{
    symbols = new QVector<QwtSymbol*>;
    colors = new QVector<QColor>;

    int r,g,b;
    for (unsigned int i = 0; i < no_vertices; i++)
    {
        r = dist(*gen);
        g = dist(*gen);
        b = dist(*gen);
        QColor color(r,g,b);
        for (unsigned int j = 0; j < i; j++)
        {
            while (color == colors->at(j))
            {
                r = dist(*gen);
                g = dist(*gen);
                b = dist(*gen);
                color = QColor(r,g,b);
            }
        }
        colors->push_back(color);
    }

    for (unsigned int i = 0; i < no_vertices; i++)
    {
        symbols->push_back(new QwtSymbol(QwtSymbol::Ellipse, QBrush(colors->at(i)), QPen(colors->at(i)), QSize(4,4)));
    }
}

void GUINodePlotter::draw_edges()
{

    std::unique_lock<std::mutex> lck(this->lock);
    QwtPlotCurve* new_curve;
    QwtPointSeriesData* new_data;
    QVector<QPointF>* new_samples;
    int i = 0;
    for (auto& e: clb::GlobalBackendController::instance()->getGraph().getEdgesAndWeights())
    {
        new_curve = new QwtPlotCurve();
        new_data = new QwtPointSeriesData();
        new_samples = new QVector<QPointF>;
        new_curve->setStyle(QwtPlotCurve::Lines);
        new_samples->push_back(QPointF(mapy[e.first.first].first,mapy[e.first.first].second));
        new_samples->push_back(QPointF(mapy[e.first.second].first,mapy[e.first.second].second));

        new_data->setSamples(*new_samples);
        new_curve->setData(new_data);
        new_curve->attach(myPlot);
        myPlot->replot();
        i++;
    }
}

void GUINodePlotter::replotSolution(backend::ClusterEncoding& clusterSol)
{
    std::unique_lock<std::mutex> lck(this->lock);
    uint64_t no_vertices = clusterSol.size();
    for (unsigned int i = 0; i < no_vertices; i++)
    {
        uint64_t cluster_id = clusterSol.getClusterOfVertex(i);
        if (!(symbols->at(cluster_id)->brush() == (markers.at(i)->symbol())->brush()))
        {
            QwtPlotMarker* mark = new QwtPlotMarker();
            //mark->setSymbol(symbols->at(cluster_id));
            mark->setSymbol(new QwtSymbol(symbols->at(cluster_id)->style(),
                QBrush(colors->at(cluster_id)),QPen(colors->at(cluster_id)), QSize(4,4)));
            mark->setValue(markers.at(i)->value());
            markers.at(i)->detach();
            markers.replace(i,mark);
        }
        markers.at(i)->attach(myPlot);
    }
    myPlot->replot();
    myPlot->show();
}


void GUINodePlotter::setPlotBackground(const uint64_t& width, const uint64_t& height)
{
    myPlot = new QwtPlot(plotWindow);

    QFont serifFont("Times", 12, QFont::Bold);

    /* axes manipulation*/
    myPlot->enableAxis(QwtPlot::xBottom);
    myPlot->enableAxis(QwtPlot::yLeft);
    myPlot->setAxisAutoScale(QwtPlot::xBottom,true);
    myPlot->setAxisAutoScale(QwtPlot::yLeft,true);

    QwtText titleX("X axis");
    titleX.setFont(serifFont);
    QwtText titleY("Y axis");
    titleY.setFont(serifFont);
    myPlot->setAxisTitle(QwtPlot::xBottom, titleX);
    myPlot->setAxisTitle(QwtPlot::yLeft, titleY);
}

void GUINodePlotter::plotContent()
{

    /* include the data into the graph */
    std::map<backend::VertexId,std::pair<double,double>>::iterator it;

    for (it = mapy.begin(); it != mapy.end(); it++)
    {
        QwtPlotMarker* mark = new QwtPlotMarker();
        mark->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::black), QPen(Qt::black), QSize(4, 4)));
        mark->setValue(QPointF((*it).second.first,(*it).second.second));
        markers.append(mark);
        markers.back()->attach(myPlot);
    }

    myPlot->replot();

}

void GUINodePlotter::clearGraph(){
    if(!mapy.empty()){
        symbols->clear();
        colors->clear();

        for(auto& e: markers)
            e->detach();

        markers.clear();
        
        mapy.clear();
        myPlot->replot();
    }
    
}


GUINodePlotter::~GUINodePlotter()
{
    if (gen != nullptr)
    {
        delete gen;
    }
    this->markers.clear();
}

}
}
