#include <QMainWindow>
#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>
#include <QtGui>
//#include "ui_myWindow.h"


class myWindow : public QMainWindow
{
	//Q_OBJECT
private:
	QWidget m_window;

public: 
	myWindow();
	~myWindow();
	
};


myWindow::myWindow(){
	m_window.show();
}

	
myWindow::~myWindow(){
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


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


    QWidget window;
    window.setLayout(layout);
    window.show();
    //uncomment the code below to have a separate main window; 
    //the code above create an entire layout with a quit button

  //  myWindow mainWin;
  //  mainWin.show();
    return app.exec();
}
