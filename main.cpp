#include <QApplication>


#include "include/GeneticGui.hpp"

using namespace clusterer::frontend;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GeneticGui& gui = GeneticGui::getApp();
    gui.startGui();

/*    QPushButton *importButton = new QPushButton("&Read Graph");
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
