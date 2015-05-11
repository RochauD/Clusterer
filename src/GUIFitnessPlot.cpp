/**
* @file GUIFitnessPlot.cpp
* @brief implementation of fitness value over time
*/

#include <QtGui>
// uncomment if needed #include <iostream>
#include "../include/GUIFitnessPlot.hpp"

#define my_delete(x) {delete x, x = NULL;}

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
    // closeFit = new QPushButton(tr("&Close"));
    // run_random = new QPushButton(tr("&Run random example"));
    plotWindow = new QWidget();

    /* setting the default background for the plot */
    setPlotBackground();

    /* add myPlot to plotWindow */
    QVBoxLayout* layout_t = new QVBoxLayout();
    layout_t->addWidget(myPlot);

    // myPlot->replot();
    // myPlot->show();

    plotWindow->setLayout(layout_t);
    plotWindow->setWindowModality(Qt::ApplicationModal);
    plotWindow->show();

    /* add zooming option */
    zoom = new QwtPlotZoomer(myPlot->canvas());
    zoom->setRubberBandPen(QPen(Qt::black, 2, Qt::DotLine));
    zoom->setTrackerPen(QPen(Qt::black));

    /*setting the layout of the main window*/
    QHBoxLayout* layout1 = new QHBoxLayout;
    // layout1->addWidget(closeFit);
    // layout1->addWidget(run_random);
    QVBoxLayout* layout2 = new QVBoxLayout;
    layout2->addLayout(layout1);
    layout2->addWidget(plotWindow);

    /*add connects*/
    //connect(closeFit,SIGNAL(clicked()),this,SLOT(close()));
    connect(this, SIGNAL(sendFitnessValue(double)), this, SLOT(replotFitness(double)));
    //connect(run_random,SIGNAL(clicked()),this,SLOT(runRandom()));

    /*setting central widget*/
    //central_vis_window = new QWidget();
    //central_vis_window->setLayout(layout2);
    //this->setCentralWidget(central_vis_window);
    this->setLayout(layout2);

    /* obtain a seed from the system clock: */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = new std::mt19937(seed);
    dist = std::uniform_real_distribution<double>(0.0,2.0);

    /* setting up the curve for fitness data */
    curve = new QwtPlotCurve("Fitness Function");
    curve->setStyle(QwtPlotCurve::Lines);
    fitness_data = new QwtPointSeriesData;
    samples = new QVector<QPointF>;
    QwtSymbol* sym = new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::blue), QPen(Qt::blue), QSize(4,4));
    curve->setSymbol(sym);

    fitness_data->setSamples(*samples);
    curve->setData(fitness_data);
    curve->attach(myPlot);

    myPlot->replot();
    myPlot->show();

}

void GUIFitnessPlot::runRandom()
{
    counter = 0;
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(genRandomValues()));
}

void GUIFitnessPlot::genRandomValues()
{
    emit sendFitnessValue(dist(*gen));
}

void GUIFitnessPlot::replotFitness(double new_value)
{

    if (counter > 10)
    {
        timer->stop();
    }

    //std::cout<<"Fitness: "<<new_value<<", x: "<<this->counter<<"\n";
    samples->push_back(QPointF(counter,new_value));
    fitness_data->setSamples(*samples);
    curve->setData(fitness_data);

    myPlot->replot();
    myPlot->show();

    this->counter++;
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
    //myPlot->setAxisScale(QwtPlot::xBottom,0,width); -- x probably automatic
    //myPlot->setAxisScale(QwtPlot::yLeft,0,height); -- y fitness in [0.0,2.0] perhaps

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