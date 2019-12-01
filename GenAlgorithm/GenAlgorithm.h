#pragma once

#include <memory>
#include <chrono>
#include <QtWidgets/QMainWindow>
#include <QtCharts>

#include "ui_GenAlgorithm.h"
#include "algorithm/PopulationManager.h"
#include "dataplotting/IterationValuePlotter.h"
#include "dataplotting/DataWriter.h"

class GenAlgorithm : public QMainWindow
{
    Q_OBJECT

public:
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    GenAlgorithm(char* argv[], QWidget *parent = Q_NULLPTR);
	
private:
    void runAlgorithm();
    void makeChartButtonsClickable();
    void saveData();
    void displayElapsedTime(const TimePoint&);
    void connectSlots();
    std::string getAppDirectory(char* argv[]);
    void displayResult();

    Ui::GenAlgorithmClass ui;
    algorithm::types::ResultsPerIteration calculatedResults;
    std::unique_ptr<dataplotting::IterationValuePlotter> plotter;
    std::unique_ptr<dataplotting::DataWriter> dataWriter;

private slots:
    void handleRunButton();
    void handleRunChartButton();
    void handleRunChartMeanButton();
    void handleRunChartStdDevButton();
    void handleSelectionMethodsGroupBox();
};
