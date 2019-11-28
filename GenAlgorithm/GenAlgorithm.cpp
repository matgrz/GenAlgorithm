#include "GenAlgorithm.h"
#include "algorithm/InputDataParser.h"

#include <QtCharts>

GenAlgorithm::GenAlgorithm(char* argv[], QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.radioButtonMS1, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS2, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS3, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));

    connect(ui.pushButtonRun, SIGNAL(released()), this, SLOT(handleRunButton()));
    connect(ui.pushButtonRunChart, SIGNAL(released()), this, SLOT(handleRunChartButton()));
    connect(ui.pushButtonRunChartMean, SIGNAL(released()), this, SLOT(handleRunChartMeanButton()));
    connect(ui.pushButtonRunChartStdDev, SIGNAL(released()), this, SLOT(handleRunChartStdDevButton()));

    std::string directory = argv[0];
    directory.erase(directory.find_last_of('\\') + 1);
    plotter = std::make_unique<dataplotting::IterationValuePlotter>();
    dataWriter = std::make_unique<dataplotting::DataWriter>(directory);
}

void GenAlgorithm::handleRunButton()
{
    using namespace std::chrono;
    auto startTime = steady_clock::now();

    const auto inputData = algorithm::InputDataParser{}.parseData(ui);
    auto populationManager = std::make_unique<algorithm::PopulationManager>(inputData);
    calculatedResults = populationManager->findTheBestSolution();
    makePlottingButtonsClickable();
    saveData();

    auto endTime = steady_clock::now();
    std::string elapsedTime = calculateElapsedTime(startTime, endTime);
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

void GenAlgorithm::makePlottingButtonsClickable()
{
    ui.pushButtonRunChart->setEnabled(true);
    ui.pushButtonRunChartMean->setEnabled(true);
    ui.pushButtonRunChartStdDev->setEnabled(true);
}

void GenAlgorithm::saveData()
{
    if (ui.checkBoxDataSave->isChecked())
        dataWriter->saveData(calculatedResults);
}

std::string GenAlgorithm::calculateElapsedTime(const TimePoint& startTime, const TimePoint& endTime)
{
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() % 1000;
    auto durationSec = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() % 60;
    auto durationMin = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();
    return "Elapsed time: " + std::to_string(durationMin) + "m " + std::to_string(durationSec) + "s " + 
           std::to_string(durationMs) + "ms";
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
