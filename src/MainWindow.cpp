/**
 * @file MainWindow.h
 * @brief Main window for the Clusterer GUI
 */

// Own headers
#include "../include/MainWindow.h"
#include "../include/SettingsDialog.h"

// External headers
#include <QMessageBox>
#include <QFileDialog>

// Generated headers
#include "ui_MainWindow.h"
#include "../include/GlobalBackendController.hpp"


namespace clusterer
{

namespace frontend
{


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window_vis = new QWidget();
    add_vis_layout = new QHBoxLayout();
    window_vis->setLayout(add_vis_layout);
    window_vis->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAlert(const QString& title, const QString& text)
{
    QMessageBox messageBox;
    messageBox.information(0, title, text);
}

void MainWindow::on_pushButton_clicked()
{
    //Start button

    clb::GlobalBackendController::instance()->loadGraphTypeVertexPairWeight("../test_files/out.ucidata-zachary");
    //clb::GlobalBackendController::instance()->runAlgorithm();

    clb::Graph graph;

    graph.addVertex(backend::Vertex(0));
    graph.addVertex(backend::Vertex(1));
    graph.addVertex(backend::Vertex(2));
    graph.addVertex(backend::Vertex(3));
    graph.addVertex(backend::Vertex(4));
    graph.addVertex(backend::Vertex(5));

    // from NYC
    graph.addEdge(backend::Vertex(0), backend::Vertex(1), 329);
    graph.addEdge(backend::Vertex(0), backend::Vertex(2), 1759.93);
    graph.addEdge(backend::Vertex(0), backend::Vertex(3), 1145.58);
    graph.addEdge(backend::Vertex(0), backend::Vertex(4), 4133.71);
    graph.addEdge(backend::Vertex(0), backend::Vertex(5), 7990.70);

    graph.addEdge(backend::Vertex(1), backend::Vertex(0), 329);
    graph.addEdge(backend::Vertex(2), backend::Vertex(0), 1759.93);
    graph.addEdge(backend::Vertex(3), backend::Vertex(0), 1145.58);
    graph.addEdge(backend::Vertex(4), backend::Vertex(0), 4133.71);
    graph.addEdge(backend::Vertex(5), backend::Vertex(0), 7990.70);  

    // from Washingon DC
    graph.addEdge(backend::Vertex(1), backend::Vertex(2), 1492.85);
    graph.addEdge(backend::Vertex(1), backend::Vertex(3), 956.26);
    graph.addEdge(backend::Vertex(1), backend::Vertex(4), 3922.93);
    graph.addEdge(backend::Vertex(1), backend::Vertex(5), 7779.88);

    graph.addEdge(backend::Vertex(2), backend::Vertex(1), 1492.85);
    graph.addEdge(backend::Vertex(3), backend::Vertex(1), 956.26);
    graph.addEdge(backend::Vertex(4), backend::Vertex(1), 3922.93);
    graph.addEdge(backend::Vertex(5), backend::Vertex(1), 7779.88);

    // from Miami
    graph.addEdge(backend::Vertex(2), backend::Vertex(3), 1919.46);
    graph.addEdge(backend::Vertex(2), backend::Vertex(4), 4174.43);
    graph.addEdge(backend::Vertex(2), backend::Vertex(5), 7825.37);

    graph.addEdge(backend::Vertex(3), backend::Vertex(2), 1919.46);
    graph.addEdge(backend::Vertex(4), backend::Vertex(2), 4174.43);
    graph.addEdge(backend::Vertex(5), backend::Vertex(2), 7825.37);

    // from Chicago
    graph.addEdge(backend::Vertex(3), backend::Vertex(4), 2988.24);
    graph.addEdge(backend::Vertex(3), backend::Vertex(5), 6845.75);

    graph.addEdge(backend::Vertex(4), backend::Vertex(3), 2988.24);
    graph.addEdge(backend::Vertex(5), backend::Vertex(3), 6845.75);

    // from San Francisco 
    graph.addEdge(backend::Vertex(4), backend::Vertex(5), 3858.23);
    graph.addEdge(backend::Vertex(5), backend::Vertex(4), 3858.23);
    
    gnp = new GUINodePlotter(this,graph,
      clb::GlobalBackendController::instance());
    
    add_vis_layout->addWidget(gnp);
    this->showAlert("Alert", "Start");
}

void MainWindow::on_pushButton_4_clicked()
{
    //Stop button
    this->showAlert("Alert", "Stop");
}

void MainWindow::on_pushButton_2_clicked()
{
    //Pause button
    this->showAlert("Alert", "Pause");
}

void MainWindow::on_pushButton_3_clicked()
{
    //Resume button
    this->showAlert("Alert", "Resume");
}

void MainWindow::on_actionSave_Settings_2_triggered()
{
    // Save settings
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Save Settings"),
                   tr("."),
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}

void MainWindow::on_actionLoad_Settings_2_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Settings File"),
                   ".",
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}

void MainWindow::on_actionSave_Graph_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Save Graph"),
                   tr("."),
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}

void MainWindow::on_actionZachary_format_triggered()
{
    // Load Zachary Format
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Zachary Karate Club Graph"),
                   ".",
                   tr("All Files (*)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}

void MainWindow::on_actionMovielens_format_triggered()
{
    // Load Movielens Format
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Open Movielens Graph"),
                   ".",
                   tr("All Files (*)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}

void MainWindow::on_actionSave_Population_triggered()
{
    // Save population
    QString path = QFileDialog::getSaveFileName(this,
                   tr("Save Population"),
                   tr("."),
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}

void MainWindow::on_actionLoad_Population_triggered()
{
    // Load population
    QString path = QFileDialog::getOpenFileName(this,
                   tr("Load Population"),
                   ".",
                   tr("Text Files (*.txt)"));
    if (!path.isNull() && !path.isEmpty())
    {
        this->showAlert("Alert", "Path is " + path);
    }
}


void MainWindow::on_actionAbout_2_triggered()
{
    QString info = "Clustring of Social Network Graphs using Genetic Algotithms\n\n\
This project was developped for the 2015 Software Engineering Lab course in Jacobs University Bremen.\
\n\nAuthors: Denis Rochau, Dinesh Kannan, Annu Thapa,\
 Valentin Vasiliu, Radu Homorozan, Kiril Kafadarov";

    QMessageBox::about(this, "About this project", info);
}

void MainWindow::on_actionEdit_Settings_triggered()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

}
}