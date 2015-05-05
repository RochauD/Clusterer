#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_label_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_clicked()
{
    //Start button
}

void MainWindow::on_pushButton_4_clicked()
{
    //Stop button
}

void MainWindow::on_pushButton_2_clicked()
{
    //Pause button
}

void MainWindow::on_pushButton_3_clicked()
{
    //Resume button
}
