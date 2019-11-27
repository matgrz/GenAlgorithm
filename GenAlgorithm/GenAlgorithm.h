#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtCharts>

#include "ui_GenAlgorithm.h"
#include "algorithm/PopulationManager.h"
#include "dataplotting/IterationValuePlotter.h"

class GenAlgorithm : public QMainWindow
{
    Q_OBJECT

public:
    GenAlgorithm(QWidget *parent = Q_NULLPTR);
	
private:
    Ui::GenAlgorithmClass ui;
    algorithm::PopulationManager::ResultsPerIteration calculatedResults;
    std::unique_ptr<dataplotting::IterationValuePlotter> plotter;

private slots:
    void handleRunButton();
    void handleRunChartButton();
    void handleRunChartMeanButton();
    void handleSelectionMethodsGroupBox();
};
