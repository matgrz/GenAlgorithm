#include "GenAlgorithm.h"
#include "algorithm/InputDataParser.h"

#include <QtCharts>

GenAlgorithm::GenAlgorithm(char* argv[], QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connectSlots();
    
    plotter = std::make_unique<dataplotting::IterationValuePlotter>();
    dataWriter = std::make_unique<dataplotting::DataWriter>(getAppDirectory(argv));
}

void GenAlgorithm::handleRunButton()
{
    auto startTime = std::chrono::steady_clock::now();
    runAlgorithm();
    displayElapsedTime(startTime);
    displayResult();
    makeChartButtonsClickable();
    saveData();
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

void GenAlgorithm::runAlgorithm()
{
    try
    {
        calculatedResults.clear();
        const auto inputData = algorithm::InputDataParser{}.parseData(ui);
        auto populationManager = std::make_unique<algorithm::PopulationManager>(inputData);
        calculatedResults = populationManager->findTheBestSolution();
    }
    catch (std::exception & e)
    {
        std::string errMsg{ "Try using different set of parameters\nError msg: " + std::string(e.what()) };
        ui.labelOutput->setText(errMsg.c_str());
    }
}

void GenAlgorithm::makeChartButtonsClickable()
{
    ui.pushButtonRunChart->setEnabled(true);
    ui.pushButtonRunChartMean->setEnabled(true);
    ui.pushButtonRunChartStdDev->setEnabled(true);
    ui.pushButtonRun->setEnabled(true);
}

void GenAlgorithm::saveData()
{
    if (ui.checkBoxDataSave->isChecked())
        dataWriter->saveData(calculatedResults);
}

void GenAlgorithm::displayElapsedTime(const TimePoint& startTime)
{
    using namespace std::chrono;
    auto endTime = steady_clock::now();
    auto durationMs = duration_cast<std::chrono::milliseconds>(endTime - startTime).count() % 1000;
    auto durationSec = duration_cast<std::chrono::seconds>(endTime - startTime).count() % 60;
    auto durationMin = duration_cast<std::chrono::minutes>(endTime - startTime).count();
    std::string elapsedTime = "Elapsed time: " + std::to_string(durationMin) + "m " + std::to_string(durationSec) +
                              "s " + std::to_string(durationMs) + "ms";
    ui.labelExecutionTime->setText(elapsedTime.c_str());
}

void GenAlgorithm::connectSlots()
{
    connect(ui.radioButtonMS1, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS2, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS3, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));

    connect(ui.pushButtonRun, SIGNAL(released()), this, SLOT(handleRunButton()));
    connect(ui.pushButtonRunChart, SIGNAL(released()), this, SLOT(handleRunChartButton()));
    connect(ui.pushButtonRunChartMean, SIGNAL(released()), this, SLOT(handleRunChartMeanButton()));
    connect(ui.pushButtonRunChartStdDev, SIGNAL(released()), this, SLOT(handleRunChartStdDevButton()));
}

std::string GenAlgorithm::getAppDirectory(char* argv[])
{
    std::string directory = argv[0];
    directory.erase(directory.find_last_of('\\') + 1);
    return directory;
}

void GenAlgorithm::displayResult()
{
    const auto bestResult = std::prev(calculatedResults.end())->second.begin();
    std::string resultString{ "Best result:  " + std::to_string(bestResult->z) +" for point\n(" +
                              std::to_string(bestResult->x) + ", " + std::to_string(bestResult->y) + ")" };
    
    ui.labelOutput->setText(resultString.c_str());
    ui.labelOutput->setAlignment(Qt::AlignCenter);
    QFont font = ui.labelOutput->font();
    font.setPointSize(10);
    font.setBold(true);
    ui.labelOutput->setFont(font);
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
