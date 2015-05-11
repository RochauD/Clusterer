/**
 * @file SettingsDialog.cpp
 * @brief The custom dialog for modifying the settings of the project
 */

// Own headers
#include "../include/SettingsDialog.h"
#include "../include/ClusteringParams.hpp"
#include "../include/GlobalBackendController.hpp"
#include "../include/FrontendConfig.h"

// External headers

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
    // Backend options
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
    params.autoSavePopulationFrequency = ui->autoSavePopulation->value();
    params.predictedClusterCount = ui->predictedClusterCount->value();
    // DO NOT MOVE AROUND THE OPTIONS FOR COMBOBOXES!!
    params.fitnessFunction = ui->fitnessFunction->currentIndex();
    params.clusterGenerationFunction = ui->clusterInitFunc->currentIndex();

    // Frontend options
    FrontendConfig::setVisualizeGraph(ui->visualizeGraph->isChecked());

    clb::GlobalBackendController::instance()->setConfigurationParameters(params);
}

}
}