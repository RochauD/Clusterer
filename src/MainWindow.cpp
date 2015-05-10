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


namespace clusterer
{

namespace frontend
{


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

void MainWindow::showAlert(const QString &title, const QString &text)
{
    QMessageBox messageBox;
    messageBox.information(0, title, text);
}


void MainWindow::on_pushButton_clicked()
{
    //Start button
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