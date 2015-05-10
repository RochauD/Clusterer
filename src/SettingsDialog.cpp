/**
 * @file SettingsDialog.cpp
 * @brief The custom dialog for modifying the settings of the project
 */

// Own headers
#include "../include/SettingsDialog.h"
#include "../include/ClusteringParams.hpp"
#include "../include/FrontendConfig.h"

// External headers
#include <QMessageBox>

// Generated headers
#include "ui_SettingsDialog.h"


namespace clusterer
{

namespace frontend
{


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    setWindowTitle(tr("Clusterer Settings"));
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    clusterer::backend::ClusteringParams params;

    params.iterationUntilMissingImprovementCausesInterruption = ui->stopNoImpr->value();
    params.maxFitness = ui->maxFitness->value();
    params.minFitness = ui->minFitness->value();
    params.maxIterations = ui->maxIter->value();
    params.minIterations = ui->minIter->value();
    params.uniquePopulationSelection = ui->uniquePopulation->isChecked();
    params.minPopulationSize = ui->minPopulation->value();
    params.maxPopulationSize = ui->maxPopulation->value();
    params.explorationMutationChance = ui->explorationMutChance->value();
    params.refinementMutationChance = ui->refinementMutChance->value();
    params.crossoverIterationCount = ui->crossoverIter->value();
    params.phaseSwitchFitnessValue = ui->phaseSwitchFitness->value();
    params.phaseSwitchIterationValue = ui->phaseSwitchIteration->value();
    params.maxMinDensityClusterProbability = ui->valiParam->value();
    params.logFrequency = ui->logFrequency->value();
    params.enqueueFrequency = ui->enqueueFrequency->value();
    params.threadCount = ui->threadCount->value();

    QString test;
    test.setNum(ui->stopNoImpr->value());

    QMessageBox::information(this, "Values", test);
    // Send params to the backend controller

    FrontendConfig::setVisualizeGraph(ui->visualizeGraph->isChecked());
}

}
}