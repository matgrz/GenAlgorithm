#include "IterationValuePlotter.h"

#include <QtWidgets>

namespace dataplotting
{
IterationValuePlotter::~IterationValuePlotter()
{
    chartLayout->deleteLater();
    chartWindow->deleteLater();
}

void IterationValuePlotter::plotIterationResults(const IterationResults& calculatedResults)
{
    clearLayoutIfAlreadyCreated();
    auto [maxY, maxX] = getMaxValuesFromIterationResults(calculatedResults);
    QScatterSeries* series = new QScatterSeries();

    for (const auto& resultPair : calculatedResults)
        series->append(resultPair.first, resultPair.second.begin()->z);

    setLayout(series, maxY, maxX);
}

void IterationValuePlotter::plotMeanValue(const IterationResults& calculatedResults)
{
    clearLayoutIfAlreadyCreated();
    float maxX = calculatedResults.size();
    float maxY{0.0};

    QScatterSeries* series = new QScatterSeries();
    for (const auto& resultPair : calculatedResults)
    {
        auto meanValue = calculateMeanValueForSingleIteration(resultPair.second);
        series->append(resultPair.first, meanValue);

        if (meanValue > maxY)
            maxY = meanValue;
    }
    setLayout(series, maxY, maxX);
}

void IterationValuePlotter::plotStdDev(const IterationResults& calculatedResults)
{
    clearLayoutIfAlreadyCreated();
    float maxX = calculatedResults.size();
    float maxY{ 0.0 };

    QScatterSeries* series = new QScatterSeries();
    for (const auto& resultPair : calculatedResults)
    {
        auto stdDev = calculateStdDevForSingleIteration(resultPair.second);
        series->append(resultPair.first, stdDev);

        if (stdDev > maxY)
            maxY = stdDev;
    }
    setLayout(series, maxY, maxX);
}

void IterationValuePlotter::clearLayoutIfAlreadyCreated()
{
    if (chartLayout != nullptr)
        chartLayout->deleteLater();
    if (chartWindow != nullptr)
        chartWindow->deleteLater();
}
std::pair<float, float> IterationValuePlotter::getMaxValuesFromIterationResults(const IterationResults& results)
{
    float maxY = results.at(0).begin()->z;
    float maxX = results.size();
    return {maxY, maxX};
}

void IterationValuePlotter::setLayout(QScatterSeries* series, float maxY, float maxX)
{
    chartWindow = new QWidget(0);
    chartLayout = new QVBoxLayout(chartWindow);
    chartLayout->addWidget(createChartView(maxY, maxX, series));
    chartWindow->setLayout(chartLayout);
    chartLayout->activate();
    chartWindow->resize(800, 640);
    chartWindow->show();
}

QChart* IterationValuePlotter::createChart(QScatterSeries* series)
{
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Lowest value for every iteration chart");
    return chart;
}

QChartView* IterationValuePlotter::createChartView(float maxY, float maxX, QScatterSeries* series)
{
    QChartView* chartView = new QChartView(createChart(series));
    chartView->setRenderHint(QPainter::Antialiasing);

    auto [axisX, axisY] = createAxes(maxY, maxX);
    chartView->chart()->setAxisY(axisY, series);
    chartView->chart()->setAxisX(axisX, series);
    return chartView;
}

std::pair<QValueAxis*, QValueAxis*> IterationValuePlotter::createAxes(float maxY, float maxX)
{
    QValueAxis* axisY = new QValueAxis;
    QValueAxis* axisX = new QValueAxis;
    axisY->setRange(0, maxY * 1.02);
    axisX->setRange(-0.05, maxX + 0.1);

    return { axisX, axisY };
}

float IterationValuePlotter::calculateMeanValueForSingleIteration(const SortedResults& sortedResults)
{
    auto sumResults = [](float lhs, const algorithm::types::ResultValues& rhs) {
                          return lhs + rhs.z;
                      };
    float elementSum = std::accumulate(sortedResults.begin(), sortedResults.end(), 0.0, sumResults);
    return elementSum / sortedResults.size();
}

float IterationValuePlotter::calculateStdDevForSingleIteration(const SortedResults& sortedResults)
{
    const auto meanValue = calculateMeanValueForSingleIteration(sortedResults);
    auto squareOfDifference = [&meanValue](float lhs, const auto& rhs) {
        return lhs + std::pow(rhs.z - meanValue, 2);
    };

    const auto sumOfPow = std::accumulate(sortedResults.begin(), sortedResults.end(), 0.0, squareOfDifference);
    return std::sqrt(sumOfPow / sortedResults.size());
}
}
