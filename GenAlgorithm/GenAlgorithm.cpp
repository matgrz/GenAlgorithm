#include "GenAlgorithm.h"
#include "algorithm/InputDataParser.h"
#include "algorithm/PopulationManager.h"

#include <iostream>
#include <chrono>
#include <QtCharts>

GenAlgorithm::GenAlgorithm(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    runButton = ui.pushButtonRun;
    runChartButton = ui.pushButtonRunChart;

    connect(ui.radioButtonMS1, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS2, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
    connect(ui.radioButtonMS3, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));

    connect(runButton, SIGNAL(released()), this, SLOT(handleRunButton()));
    connect(runChartButton, SIGNAL(released()), this, SLOT(handleRunChartButton()));
}

void GenAlgorithm::handleRunButton()
{
    using namespace std::chrono;
    auto startTime = steady_clock::now();
    const auto inputData = algorithm::InputDataParser{}.parseData(ui);
    auto populationManager = std::make_unique<algorithm::PopulationManager>(inputData);
    populationManager->findTheBestSolution();

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
    std::cout << "in run chart\n";
    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
	
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget* chartWindow = new QWidget(0);

    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(480, 320);
    chartWindow->show();
}
