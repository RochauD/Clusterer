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
    myWindow mainWin;
  //  mainWin.show();
    return app.exec();
}
