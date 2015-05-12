/**
 * @file MainWindow.h
 * @brief Main window for the Clusterer GUI
 */

// standard headers
#include <limits>

// Own headers
#include "../include/MainWindow.h"
#include "../include/SettingsDialog.h"
#include "../include/PopulationMember.hpp"
#include "../include/IntegerVectorEncoding.hpp"
#include "../include/FrontendConfig.h"
#include "../include/GlobalBackendController.hpp"
#include "../include/GlobalFileLogger.hpp"

// External headers
#include <QMessageBox>
#include <QFileDialog>

// Generated headers
#include "ui_MainWindow.h"

#define MSEC_60_HZ 16


namespace clusterer
{

namespace frontend
{


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateFrontend()));

    setStateAlgoOff();
    // No graph loaded - cannot start
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStateAlgoOn()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
    ui->actionZachary_format->setEnabled(false);
    ui->actionMovielens_format->setEnabled(false);
    ui->actionLoad_Population->setEnabled(false);
    ui->actionSave_Population->setEnabled(false);
}

void MainWindow::setStateAlgoOff()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->actionZachary_format->setEnabled(true);
    ui->actionMovielens_format->setEnabled(true);
    ui->actionLoad_Population->setEnabled(true);
    ui->actionSave_Population->setEnabled(true);
}

void MainWindow::updateFrontend()
{
    std::pair<clb::PopulationMember<clb::IntegerVectorEncoding, double>, uint64_t> output;
    std::vector<std::pair<clb::PopulationMember<clb::IntegerVectorEncoding, double>, uint64_t>> vector;
    while (clb::GlobalBackendController::instance()->getOutQueue()->popNonWaiting(output))
    {
        vector.push_back(output);
    }

    if (!vector.empty())
    {
        bool exitFlag = false;
        std::vector<std::pair<uint64_t, double>> fitnessVec;
        fitnessVec.reserve(vector.size());
        for (auto& e : vector)
        {
            if (std::numeric_limits<uint64_t>::max() - std::numeric_limits<uint64_t>::epsilon() <= e.second)
            {
                // algo stopped
                setAlgorithmRunning(false);
                setStateAlgoOff();
                timer.stop();
                exitFlag = true;
                continue;
            }
            fitnessVec.push_back(std::make_pair(e.second, e.first.fitnessValue));
        }
        ui->fitnessPlotter->replotFitness(fitnessVec);

        if (FrontendConfig::getVisualizeGraph())
        {
            if (exitFlag == true && vector.size() > 1)
            {
                ui->nodePlotter->replotSolution(vector[vector.size() - 2].first.populationEncoding);
            }
            else
            {
                ui->nodePlotter->replotSolution(vector[vector.size() - 1].first.populationEncoding);
            }
        }
    }
}

void MainWindow::setAlgorithmRunning(bool val)
{
    algorithmRunning = val;
}

bool MainWindow::isAlgorithmRunning()
{
    return algorithmRunning;
}

void MainWindow::showAlert(const QString& title, const QString& text)
{
    QMessageBox::information(this, title, text);
}

void MainWindow::on_pushButton_clicked()
{
    //Start button
    // @todo put check condition function into controller and call it here and check
    if (clb::GlobalBackendController::instance()->runAlgorithm(true))
    {
        clb::GlobalBackendController::instance()->runAlgorithm(true);
        timer.start(MSEC_60_HZ);
        this->showAlert("Info", "Started the algorithm");
        setStateAlgoOn();
        setAlgorithmRunning(true);
    }
    else
    {
        clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Could not start the algorithm as you need to load a Graph first.");
        QMessageBox::critical(this, "Error", "Could not start the algorithm as you need to load a Graph first.");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //Stop button
    clb::GlobalBackendController::instance()->stopAlgorithm();
    this->showAlert("Alert", "Stopped the algorithm");
    setStateAlgoOff();
    setAlgorithmRunning(true);
    timer.stop();
    ui->nodePlotter->clearGraph();
    ui->fitnessPlotter->clearFitness();
}

void MainWindow::on_pushButton_2_clicked()
{
    clb::GlobalBackendController::instance()->stopAlgorithm();
    setStateAlgoOff();
    setAlgorithmRunning(false);
    this->showAlert("Alert", "Paused algorithm");
    timer.stop();
    ui->pushButton_3->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    clb::GlobalBackendController::instance()->runAlgorithm(false);
    this->showAlert("Alert", "Resumed execution of the algorithm");
    timer.start(MSEC_60_HZ);
    setStateAlgoOn();
    setAlgorithmRunning(true);
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
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Save Settings failed. Failed saving settings.");
            QMessageBox::critical(this, "Save Settings failed", "Failed saving settings.");
        }
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
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Load Settings failed. The file you selected is not a valid configuration file");
            QMessageBox::critical(this, "Load Settings failed", "The file you selected is not a valid configuration file");
        }
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
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Save Graph failed. Unable to save graph");
            QMessageBox::critical(this, "Save Graph failed", "Unable to save graph");
        }
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
            ui->pushButton->setEnabled(true);
            if (FrontendConfig::getVisualizeGraph())
            {
                ui->nodePlotter->initGraph();     
            }
        }
        else
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Load Graph failed. Unable to load a vertex-pair-weight graph");
            QMessageBox::critical(this, "Load Graph failed", "Unable to load a vertex-pair-weight graph");
        }
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
            ui->pushButton->setEnabled(true);
            if (FrontendConfig::getVisualizeGraph())
            {
                ui->nodePlotter->initGraph();     
            }
        }
        else
        {
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Load Graph failed. Unable to load a Movielens graph");
            QMessageBox::critical(this, "Load Graph failed", "Unable to load a Movielens graph");
        }
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
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Save Population failed. Unable to save population");
            QMessageBox::critical(this, "Save Population failed", "Unable to save population");
        }
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
            clc::GlobalFileLogger::instance()->log(clc::SeverityType::ERROR, "Load Population failed. Unable to load a population out of this file.");
            QMessageBox::critical(this, "Load Population failed", "Unable to load a population out of this file.");
        }
    }
}


void MainWindow::on_actionAbout_2_triggered()
{
    QString info = "Clustering Social Networks by using Genetic Algorithms\n\n"
                   "Software Project for the Course Software Engineering Lab 2015 at Jacobs University Bremen.\n\n"
                   "Authors: Denis Rochau, Dinesh Kannan, Annu Thapa, Valentin Vasiliu, Radu Homorozan, Kiril Kafadarov";
    QMessageBox::about(this, "About this project", info);
}

void MainWindow::on_actionEdit_Settings_triggered()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

}
}
