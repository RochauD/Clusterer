#include <QApplication>


#include "include/MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //clusterer::frontend::MainWindow w;
    //w.show();
    clb::Graph graph;

    graph.addVertex(clb::Vertex(0));
    graph.addVertex(clb::Vertex(1));
    graph.addVertex(clb::Vertex(2));
    graph.addVertex(clb::Vertex(3));
    graph.addVertex(clb::Vertex(4));
    graph.addVertex(clb::Vertex(5));

    // from NYC
    graph.addEdge(clb::Vertex(0), clb::Vertex(1), 329);
    graph.addEdge(clb::Vertex(0), clb::Vertex(2), 1759.93);
    graph.addEdge(clb::Vertex(0), clb::Vertex(3), 1145.58);
    graph.addEdge(clb::Vertex(0), clb::Vertex(4), 4133.71);
    graph.addEdge(clb::Vertex(0), clb::Vertex(5), 7990.70);

    graph.addEdge(clb::Vertex(1), clb::Vertex(0), 329);
    graph.addEdge(clb::Vertex(2), clb::Vertex(0), 1759.93);
    graph.addEdge(clb::Vertex(3), clb::Vertex(0), 1145.58);
    graph.addEdge(clb::Vertex(4), clb::Vertex(0), 4133.71);
    graph.addEdge(clb::Vertex(5), clb::Vertex(0), 7990.70);  

    // from Washingon DC
    graph.addEdge(clb::Vertex(1), clb::Vertex(2), 1492.85);
    graph.addEdge(clb::Vertex(1), clb::Vertex(3), 956.26);
    graph.addEdge(clb::Vertex(1), clb::Vertex(4), 3922.93);
    graph.addEdge(clb::Vertex(1), clb::Vertex(5), 7779.88);

    graph.addEdge(clb::Vertex(2), clb::Vertex(1), 1492.85);
    graph.addEdge(clb::Vertex(3), clb::Vertex(1), 956.26);
    graph.addEdge(clb::Vertex(4), clb::Vertex(1), 3922.93);
    graph.addEdge(clb::Vertex(5), clb::Vertex(1), 7779.88);

    // from Miami
    graph.addEdge(clb::Vertex(2), clb::Vertex(3), 1919.46);
    graph.addEdge(clb::Vertex(2), clb::Vertex(4), 4174.43);
    graph.addEdge(clb::Vertex(2), clb::Vertex(5), 7825.37);

    graph.addEdge(clb::Vertex(3), clb::Vertex(2), 1919.46);
    graph.addEdge(clb::Vertex(4), clb::Vertex(2), 4174.43);
    graph.addEdge(clb::Vertex(5), clb::Vertex(2), 7825.37);

    // from Chicago
    graph.addEdge(clb::Vertex(3), clb::Vertex(4), 2988.24);
    graph.addEdge(clb::Vertex(3), clb::Vertex(5), 6845.75);

    graph.addEdge(clb::Vertex(4), clb::Vertex(3), 2988.24);
    graph.addEdge(clb::Vertex(5), clb::Vertex(3), 6845.75);

    // from San Francisco 
    graph.addEdge(clb::Vertex(4), clb::Vertex(5), 3858.23);
    graph.addEdge(clb::Vertex(5), clb::Vertex(4), 3858.23);

    clb::GlobalBackendController::instance()->loadGraphTypeVertexPairWeight("../test_files/out.ucidata-zachary");
  
    clusterer::frontend::GUINodePlotter gnp(NULL,clb::GlobalBackendController::instance()->getGraph(),
        clb::GlobalBackendController::instance());
    gnp.show();

   /* QApplication app(argc, argv);

    GeneticGui& gui = GeneticGui::getApp();
    gui.startGui();

    QPushButton *importButton = new QPushButton("&Read Graph");
    QPushButton *settingsButton = new QPushButton("&Settings");
    QPushButton *quitButton = new QPushButton("&Quit");
    
    //implement quit button
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    
    QVBoxLayout *layout = new QVBoxLayout;

    //add buttons to window in specified order
    layout->addWidget(importButton);
    layout->addWidget(settingsButton);
    layout->addWidget(quitButton);


    myWindow window;
    window.setLayout(layout);
    window.show();*/
    //uncomment the code below to have a separate main window; 
    //the code above create an entire layout with a quit button

  //  myWindow mainWin;
  //  mainWin.show();
    return app.exec();
}
