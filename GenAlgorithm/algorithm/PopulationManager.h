#pragma once

#include <vector>
#include <memory>
#include <map>
#include <set>

#include "types/InputData.h"
#include "types/MainTypes.h"
#include "selection/ISelector.h"
#include "crossover/ICrossover.h"
#include "mutation/IMutator.h"

namespace algorithm
{
class PopulationManager
{
public:
    PopulationManager(const types::InputData&);
    types::ResultsPerIteration findTheBestSolution() const;

private:
    types::Population initilizePopulation() const;
    std::map<float, types::Point> calculateValuesAndStoreIt(const types::Population&, 
                                                            types::ResultsPerIteration&,
                                                            const int) const;
    types::Population convertResultsToPopulation(const std::map<float, types::Point>&) const;
    float calculateValue(float, float) const;
    types::Population getElites(const std::map<float, types::Point>&) const;
    types::Population addElitesToPopulationIfNecessary(types::Population, const types::Population&) const;
    void adjustPopulationSize(types::Population&) const;

    const types::InputData input;
    std::unique_ptr<selection::ISelector> selector;
    std::unique_ptr<crossover::ICrossover> crossover;
    std::unique_ptr<mutation::IMutator> mutator;
    const float xMin;
    const float xMax;
    const float yMin;
    const float yMax;
};
}
