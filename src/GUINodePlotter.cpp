/**
* @file GUINodePlotter.cpp
* @brief class to visually plot the result of implementation of a transformer to obtain
*  coordinates for a graph's nodes using the edge's weights
*/

#include <QtGui>
#include <iostream>
#include "../include/GUINodePlotter.hpp"

#define my_delete(x) {delete x, x = NULL;}

namespace clusterer
{
namespace frontend
{

void GUINodePlotter::printEncoding(const backend::ClusterEncoding& clusterSol){
    uint64_t no_vertices = clusterSol.size();
    std::cout<<"Encoding: \n";
    for(unsigned int i = 0; i < no_vertices; i++){
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    for(unsigned int i = 0; i < no_vertices; i++){
        std::cout<<clusterSol.getClusterOfVertex(i)<<" ";
    }
    std::cout<<"\n";
}

void GUINodePlotter::printMap(const std::map<backend::VertexId,std::pair<double,double>>& mapy)
{
    std::cout<<"\n";
    for(auto& billy : mapy){
        std::cout<<"Vertex "<<billy.first;
        std::cout<<": ("<<billy.second.first<<" , "<<billy.second.second<<")\n";
    }
}

GUINodePlotter::GUINodePlotter(QWidget *parent, uint64_t width, uint64_t height)
    : QWidget(parent)
{  

    /* testing input information */
    //std::cout<<"graph edges GUINodePlotter: "<<clb::GlobalBackendController::instance()->getGraph().getNoEdges()<<"\n";
    GraphCoordinateTransformer gt(clb::GlobalBackendController::instance()->getGraph());
    mapy = gt.getNormalizedMap(width,height);
    //printMap(mapy);

    /* resizing window */
    this->resize(width,height);

    /*creating the necessary widgets*/
    show_edges = new QPushButton(tr("&Show edges"));
    closeViz = new QPushButton(tr("&Close"));
    plotWindow = new QWidget();
    
    /* setting the default background for the plot */
    setPlotBackground(width,height);

    /* add myPlot to plotWindow */
    QVBoxLayout *layout_t = new QVBoxLayout();
    layout_t->addWidget(myPlot);

    myPlot->replot();
    myPlot->show();

    plotWindow->setLayout(layout_t);
    plotWindow->setWindowModality(Qt::ApplicationModal);
    plotWindow->show();
    
    /* add zooming option */
    zoom = new QwtPlotZoomer(myPlot->canvas());
    zoom->setRubberBandPen(QPen(Qt::black, 2, Qt::DotLine));
    zoom->setTrackerPen(QPen(Qt::black));

    /*setting the layout of the main window*/
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(show_edges);
    layout1->addWidget(closeViz);
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addLayout(layout1);
    layout2->addWidget(plotWindow);

    /*add connects*/
    connect(closeViz,SIGNAL(clicked()),this,SLOT(close()));
    connect(show_edges,SIGNAL(clicked()),this,SLOT(draw_edges()));
    
    plotContent();

    /*setting central widget*/
    //central_vis_window = new QWidget();
    //central_vis_window->setLayout(layout2);
    //this->addWidget(central_vis_window);
    this->setLayout(layout2);

    /* generate symbols for the clusters */
    /* obtain a seed from the system clock: */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = new std::mt19937(seed);
    dist = std::uniform_int_distribution<int>(0,255);
    setSymbols(clb::GlobalBackendController::instance()->getGraph().getNoVertices());

    connect(this,SIGNAL(sendSol(backend::ClusterEncoding&)),
        this,SLOT(replotSolution(backend::ClusterEncoding&)),Qt::DirectConnection);
    connect(this,SIGNAL(drawEdges()),this,SLOT(draw_edges()));

    /*
    solution = backend::IntegerVectorEncoding(&graph);
    solution.addToCluster(0,0);
    solution.addToCluster(1,1);
    solution.addToCluster(2,2);
    solution.addToCluster(3,3);
    solution.addToCluster(4,4);
    solution.addToCluster(5,5);*/
    
    //counter = 0;
    //timer = new QTimer(this);
    //timer->start(1000);
    //connect(timer,SIGNAL(timeout()),this,SLOT(genSol2()));
}

void GUINodePlotter::setSymbols(uint64_t no_vertices){
    symbols = new QVector<QwtSymbol>;
    colors = new QVector<QColor>;
    int r,g,b;
    for(unsigned int i = 0; i < no_vertices; i++){
        r = dist(*gen);
        g = dist(*gen);
        b = dist(*gen);       
        QColor color(r,g,b);
        for(unsigned int j = 0; j < i; j++){
            while(color == colors->at(j)){
                r = dist(*gen);
                g = dist(*gen);
                b = dist(*gen);
                color = QColor(r,g,b);
            }
        }
        colors->push_back(color);
    }

    for(unsigned int i = 0; i < no_vertices; i++){
        QwtSymbol sym(QwtSymbol::Ellipse,QBrush(colors->at(i)),QPen(colors->at(i)),QSize(4,4));
        symbols->push_back(sym);
    }
}

void GUINodePlotter::draw_edges(){

    std::unique_lock<std::mutex> lck (this->lock);
    QwtPlotCurve *new_curve;
    QwtPointSeriesData *new_data;
    QVector<QPointF> *new_samples;
    int i = 0;
    for(auto& e: clb::GlobalBackendController::instance()->getGraph().getEdgesAndWeights()){
        new_curve = new QwtPlotCurve();
        new_data = new QwtPointSeriesData();
        new_samples = new QVector<QPointF>;
        new_curve->setStyle(QwtPlotCurve::Lines);
        new_samples->push_back(QPointF(mapy[e.first.first].first,mapy[e.first.first].second));
        new_samples->push_back(QPointF(mapy[e.first.second].first,mapy[e.first.second].second));
        
        // std::cout<<"edge "<<i<<": ( "<<mapy[e.first.first].first<<", "<<mapy[e.first.first].second<<" )";
        // std::cout<<" --> "<<"( "<<mapy[e.first.second].first<<", "<<mapy[e.first.second].second<<")\n";

        // maybe take a look later for changing line color using symbols
        /*if(*(markers.at(e.first.first)->symbol()) == *(markers.at(e.first.second)->symbol()))
        {
            std::cout<<"checking symbol\n";
            new_curve->setSymbol(markers.at(e.first.first)->symbol());  
        } else {
            new_curve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse,QBrush(Qt::black),QPen(Qt::black),QSize(2,2)));
        }*/
       
        new_data->setSamples(*new_samples);
        new_curve->setData(new_data);
        new_curve->attach(myPlot);
        myPlot->replot();
        i++;
    }
}

void GUINodePlotter::replotSolution(backend::ClusterEncoding& clusterSol){
    std::unique_lock<std::mutex> lck (this->lock);
    uint64_t no_vertices = clusterSol.size();
    printEncoding(clusterSol);
    for(unsigned int i = 0; i < no_vertices; i++){
        uint64_t cluster_id = clusterSol.getClusterOfVertex(i);
        if(!(symbols->at(cluster_id) == *(markers.at(i)->symbol()))) {
            QwtPlotMarker *mark = new QwtPlotMarker();
            mark->setSymbol(&(symbols->at(cluster_id)));
            mark->setValue(markers.at(i)->value());
            markers.replace(i,mark);
        }
        markers.at(i)->attach(myPlot);
    }
    myPlot->replot();
    myPlot->show();
    std::cout<<"---> replotSolution end <---\n";
}


void GUINodePlotter::setPlotBackground(const uint64_t& width, const uint64_t& height){

    myPlot = new QwtPlot(plotWindow);
    myPlot->setTitle(QwtText("Graph Visualization"));

    QFont serifFont("Times", 12, QFont::Bold);

    /* legend */
    //QwtLegend *legend = new QwtLegend;
    //legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    //myPlot->insertLegend(legend, QwtPlot::BottomLegend);

    /* axes manipulation*/
    myPlot->enableAxis(QwtPlot::xBottom);
    myPlot->enableAxis(QwtPlot::yLeft);
    //myPlot->setAxisAutoScale(QwtPlot::xBottom,true);
    //myPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    myPlot->setAxisScale(QwtPlot::xBottom,0,width);
    myPlot->setAxisScale(QwtPlot::yLeft,0,height);

    QwtText titleX("X axis");
    titleX.setFont(serifFont);
    QwtText titleY("Y axis");
    titleY.setFont(serifFont);
    myPlot->setAxisTitle(QwtPlot::xBottom, titleX);
    myPlot->setAxisTitle(QwtPlot::yLeft, titleY);
}

void GUINodePlotter::plotContent(){

    /* include the data into the graph */
    curve = new QwtPlotCurve("Cluster Visualization");
    curve->setStyle(QwtPlotCurve::Dots);
    mydata = new QwtPointSeriesData;
    samples = new QVector<QPointF>;

    QwtSymbol *sym = new QwtSymbol(QwtSymbol::Ellipse,QBrush(Qt::black),QPen(Qt::black),QSize(4,4));
    curve->setSymbol(sym);

    std::map<backend::VertexId,std::pair<double,double>>::iterator it;
    for(it = mapy.begin(); it != mapy.end(); it++){
        samples->push_back(QPointF((*it).second.first,(*it).second.second));
        QwtPlotMarker *mark = new QwtPlotMarker();
        mark->setSymbol(sym);
        mark->setValue(QPointF((*it).second.first,(*it).second.second));
        markers.append(mark);
    }

    mydata->setSamples(*samples);
    curve->setData(mydata);
    curve->attach(myPlot);

    myPlot->replot();

}

GUINodePlotter::~GUINodePlotter(){
    //empty dtor
}


/*void GUINodePlotter::genSol2(){
    if(counter > 5) timer->stop();
    counter++;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0,solution.size()-1);
    solution.addToCluster(dist(gen),dist(gen));
    solution.addToCluster(dist(gen),dist(gen));
    solution.addToCluster(dist(gen),dist(gen));
    solution.addToCluster(dist(gen),dist(gen));
    emit sendSol(solution);
    emit drawEdges();
}*/
/*
void GUINodePlotter::genSolution(backend::ClusterEncoding& clusterSol){
    if(counter > 5) timer->stop();
    counter++;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0,clusterSol.size()-1);
    clusterSol.addToCluster(dist(gen),dist(gen));
    clusterSol.addToCluster(dist(gen),dist(gen));
    clusterSol.addToCluster(dist(gen),dist(gen));
    clusterSol.addToCluster(dist(gen),dist(gen));
    emit sendSol(clusterSol);
}*/

}
}
