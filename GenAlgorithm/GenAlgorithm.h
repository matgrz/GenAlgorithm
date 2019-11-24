#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include <QPushButton>

#include "ui_GenAlgorithm.h"

class GenAlgorithm : public QMainWindow
{
	Q_OBJECT

public:
	GenAlgorithm(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::GenAlgorithmClass ui;
	QPushButton* runButton;
	QPushButton* runChartButton;

private slots:
	void handleRunButton();
	void handleRunChartButton();
	void handleSelectionMethodsGroupBox();
};
