#pragma once

//#include "../algorithm/PopulationManager.h"
#include "MainTypes.h"
#include <QtCharts>

namespace dataplotting
{
class IterationValuePlotter
{
public:
    using IterationResults = algorithm::types::ResultsPerIteration;
    using SortedResults = algorithm::types::SortedResults;

    ~IterationValuePlotter();
    void plotIterationResults(const IterationResults&);
    void plotMeanValue(const IterationResults&);
    void plotStdDev(const IterationResults&);

private:
    void clearLayoutIfAlreadyCreated();
    std::pair<float, float> getMaxValuesFromIterationResults(const IterationResults&);
    void setLayout(QScatterSeries*, float, float);
    QChart* createChart(QScatterSeries*);
    QChartView* createChartView(float, float, QScatterSeries*);
    std::pair<QValueAxis*, QValueAxis*> createAxes(float, float);
    float calculateMeanValueForSingleIteration(const SortedResults&);
    float calculateStdDevForSingleIteration(const SortedResults&);

    QVBoxLayout* chartLayout{ nullptr };
    QWidget* chartWindow{ nullptr };
};
}
