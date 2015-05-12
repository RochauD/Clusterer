/**
* @file GUIFitnessPlot.cpp
* @brief implementation of fitness value over time
*/

#include <QtGui>
// uncomment if needed #include <iostream>
#include "../include/GUIFitnessPlot.hpp"

namespace clusterer
{
namespace frontend
{

GUIFitnessPlot::GUIFitnessPlot(QWidget* parent, uint64_t width, uint64_t height)
    : QWidget(parent)
{
    /* resizing window */
    this->resize(width,height);

    /*creating the necessary widgets*/
    plotWindow = new QWidget();

    /* setting the default background for the plot */
    setPlotBackground();

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
    QVBoxLayout* layout2 = new QVBoxLayout;
    layout2->addLayout(layout1);
    layout2->addWidget(plotWindow);
    this->setLayout(layout2);

    /* setting up the curve for fitness data */
    curve = new QwtPlotCurve("Fitness Function");
    curve->setStyle(QwtPlotCurve::Lines);
    fitness_data = new QwtPointSeriesData;
    samples = new QVector<QPointF>;
    QwtSymbol* sym = new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::blue), QPen(Qt::blue), QSize(4,4));
    curve->setSymbol(sym);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    fitness_data->setSamples(*samples);
    curve->setData(fitness_data);
    curve->attach(myPlot);

    myPlot->replot();
    myPlot->show();
}

void GUIFitnessPlot::replotFitness(std::vector<std::pair<uint64_t, double>> vector)
{
    for (auto& e : vector)
    {
        samples->push_back(QPointF(e.first, e.second));
    }
    fitness_data->setSamples(*samples);
    curve->setData(fitness_data);
    myPlot->replot();
    myPlot->show();
}

void GUIFitnessPlot::clearFitness(){
    //@todo
        samples->clear();
        fitness_data->setSamples(*samples);
        curve->setData(fitness_data);
        myPlot->replot();
        //myPlot->show();

}

void GUIFitnessPlot::setPlotBackground()
{

    myPlot = new QwtPlot(plotWindow);
    // myPlot->setTitle(QwtText("Fitness Analyzer"));

    QFont serifFont("Times", 12, QFont::Bold);

    /* legend */
    QwtLegend* legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    myPlot->insertLegend(legend, QwtPlot::BottomLegend);

    /* axes manipulation*/
    myPlot->enableAxis(QwtPlot::xBottom);
    myPlot->enableAxis(QwtPlot::yLeft);
    myPlot->setAxisAutoScale(QwtPlot::xBottom,true);
    myPlot->setAxisAutoScale(QwtPlot::yLeft,true);

    QwtText titleX("Time axis");
    titleX.setFont(serifFont);
    QwtText titleY("Fitness axis");
    titleY.setFont(serifFont);
    myPlot->setAxisTitle(QwtPlot::xBottom, titleX);
    myPlot->setAxisTitle(QwtPlot::yLeft, titleY);
}

GUIFitnessPlot::~GUIFitnessPlot()
{
    //empty dtor
}

}
}