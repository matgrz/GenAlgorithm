#include "GenAlgorithm.h"
#include "algorithm/InputDataParser.h"

#include <iostream>
#include <chrono>
#include <QtCharts>

GenAlgorithm::GenAlgorithm(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.radioButtonMS1, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS2, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS3, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));

    connect(ui.pushButtonRun, SIGNAL(released()), this, SLOT(handleRunButton()));
    connect(ui.pushButtonRunChart, SIGNAL(released()), this, SLOT(handleRunChartButton()));
    connect(ui.pushButtonRunChartMean, SIGNAL(released()), this, SLOT(handleRunChartMeanButton()));
    connect(ui.pushButtonRunChartStdDev, SIGNAL(released()), this, SLOT(handleRunChartStdDevButton()));

    plotter = std::make_unique<dataplotting::IterationValuePlotter>();
}

void GenAlgorithm::handleRunButton()
{
    using namespace std::chrono;
    auto startTime = steady_clock::now();
    const auto inputData = algorithm::InputDataParser{}.parseData(ui);
    auto populationManager = std::make_unique<algorithm::PopulationManager>(inputData);
    calculatedResults = populationManager->findTheBestSolution();
    // TODO make chart generation buttons clickable method
    ui.pushButtonRunChart->setEnabled(true);
    ui.pushButtonRunChartMean->setEnabled(true);
    ui.pushButtonRunChartStdDev->setEnabled(true);

    auto endTime = steady_clock::now();
    std::string elapsedTime = "Elapsed time (miliseconds): " + std::to_string(duration_cast<milliseconds>(endTime - startTime).count());
    ui.labelExecutionTime->setText(elapsedTime.c_str());
}

void GenAlgorithm::handleSelectionMethodsGroupBox()
{
    if (ui.radioButtonMS1->isChecked())
        ui.labelSelectionInfo->setText("Saved creatures [%]");
    if (ui.radioButtonMS2->isChecked())
        ui.labelSelectionInfo->setText("Roulette kill count");
    if (ui.radioButtonMS3->isChecked())
        ui.labelSelectionInfo->setText("Single tournament size");
}

void GenAlgorithm::handleRunChartButton()
{	
    plotter->plotIterationResults(calculatedResults);
}

void GenAlgorithm::handleRunChartMeanButton()
{
    plotter->plotMeanValue(calculatedResults);
}

void GenAlgorithm::handleRunChartStdDevButton()
{
    plotter->plotStdDev(calculatedResults);
}
