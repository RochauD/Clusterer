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
#include "../include/GlobalFileLogger.hpp"



namespace clusterer
{

namespace frontend
{


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAlert(const QString& title, const QString& text)
{
    QMessageBox::information(this, title, text);
}

void MainWindow::on_pushButton_clicked()
{
    //Start button

    clb::GlobalBackendController::instance()->loadGraphTypeVertexPairWeight("../test_files/out.ucidata-zachary");
    clb::GlobalBackendController::instance()->runAlgorithm(true);
    this->showAlert("Info", "Started the algorithm");
}

void MainWindow::on_pushButton_4_clicked()
{
    //Stop button
    clb::GlobalBackendController::instance()->stopAlgorithm();
    this->showAlert("Alert", "Stop");
}

void MainWindow::on_pushButton_2_clicked()
{
    clb::GlobalBackendController::instance()->stopAlgorithm();
    this->showAlert("Alert", "Pause");
}

void MainWindow::on_pushButton_3_clicked()
{
    clb::GlobalBackendController::instance()->runAlgorithm(false);
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
        bool result = clb::GlobalBackendController::instance()->saveConfiguration(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Save Settings Success", "Successfully saved settings");
        }
        else
        {
            showAlert("Save Settings failed", "Failed saving settings.");
        }
    }
    else
    {
        showAlert("Save Settings failed", "You didn't select a valid path");
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
        bool result = clb::GlobalBackendController::instance()->loadConfiguration(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Settings Success", "Successfully loaded settings");
        }
        else
        {
            showAlert("Load Settings failed", "The file you selected is not a valid configuration file");
        }
    }
    else
    {
        showAlert("Load Settings failed", "You didn't select a valid file");
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
        bool result = clb::GlobalBackendController::instance()->saveGraphToFile(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Save Graph Success", "Successfully saved graph to file.");
        }
        else
        {
            showAlert("Save Graph failed", "Unable to save graph");
        }
    }
    else
    {
        showAlert("Save Graph failed", "You didn't select a valid file");
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
        bool result = clb::GlobalBackendController::instance()->loadGraphTypeVertexPairWeight(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Graph Success", "Successfully loaded a vertex-pair-weight type graph.");
        }
        else
        {
            showAlert("Load Graph failed", "Unable to load a vertex-pair-weight graph");
        }
    }
    else
    {
        showAlert("Load Graph failed", "You didn't select a valid file");
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
        bool result = clb::GlobalBackendController::instance()->loadGraphTypeMovieLens(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Graph Success", "Successfully loaded a Movielens type graph.");
        }
        else
        {
            showAlert("Load Graph failed", "Unable to load a Movielens graph");
        }
    }
    else
    {
        showAlert("Load Graph failed", "You didn't select a valid file");
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
        bool result = clb::GlobalBackendController::instance()->savePopulation(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Save Population Success", "Successfully saved population to file.");
        }
        else
        {
            showAlert("Save Population failed", "Unable to save population");
        }
    }
    else
    {
        showAlert("Save Population failed", "You didn't select a valid file");
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
        bool result = clb::GlobalBackendController::instance()->loadPopulation(path.toLocal8Bit().constData());
        if (result == true)
        {
            showAlert("Load Population Success", "Successfully loaded a population.");
        }
        else
        {
            showAlert("Load Population failed", "Unable to load a population out of this file.");
        }
    }
    else
    {
        showAlert("Load Population failed", "You didn't select a valid file");
    }
}


void MainWindow::on_actionAbout_2_triggered()
{
    QString info = "Clustering Social Networks by using Genetic Algorithms\n\nSoftware Project for the Course Software Engineering Lab 2015 at Jacobs University Bremen.\n\nAuthors: Denis Rochau, Dinesh Kannan, Annu Thapa, Valentin Vasiliu, Radu Homorozan, Kiril Kafadarov";
    QMessageBox::about(this, "About this project", info);
}

void MainWindow::on_actionEdit_Settings_triggered()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

}
}