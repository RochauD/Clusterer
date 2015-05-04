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
    QPushButton *quitButton = new QPushButton("&Quit");
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    QVBoxLayout *layout = new QVBoxLayout;
   // layout->addWidget(mainWin);
    layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);
    window.show();
  //  mainWin.show();
    return app.exec();
}
