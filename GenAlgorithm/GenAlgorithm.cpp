#include "GenAlgorithm.h"
#include "algorithm/InputDataParser.h"
#include "algorithm/PopulationManager.h"

#include <iostream>
#include <QtCharts>

GenAlgorithm::GenAlgorithm(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	runButton = ui.pushButtonRun;
	runChartButton = ui.pushButtonRunChart;
	radioMs1 = ui.radioButtonMS1;
	radioMs2 = ui.radioButtonMS2;
	radioMs3 = ui.radioButtonMS3;

	connect(radioMs1, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
	connect(radioMs2, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));
	connect(radioMs3, SIGNAL(released()), this, SLOT(handleSelectionMethodsGroupBox()));

	connect(runButton, SIGNAL(released()), this, SLOT(handleRunButton()));
	connect(runChartButton, SIGNAL(released()), this, SLOT(handleRunChartButton()));
}

void GenAlgorithm::handleRunButton()
{
	const auto inputData = algorithm::InputDataParser{}.parseData(ui);
	auto populationManager = std::make_unique<algorithm::PopulationManager>(inputData);
	populationManager->findTheBestSolution();
}

void GenAlgorithm::handleSelectionMethodsGroupBox()
{
	if (radioMs1->isChecked())
		ui.labelSelectionInfo->setText("Saved creatures [%]");
	if (radioMs2->isChecked())
		ui.labelSelectionInfo->setText("Roulette kill count");
	if (radioMs3->isChecked())
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

	//QMainWindow window;
	//window.setCentralWidget(chartView);
	//window.resize(400, 300);
	//window.show();
	QWidget* chartWindow = new QWidget(0);

	QVBoxLayout* layout = new QVBoxLayout(chartWindow);
	layout->addWidget(chartView);
	chartWindow->setLayout(layout);
	layout->activate();
	chartWindow->resize(480, 320);
	chartWindow->show();
}
