#pragma once

#include <vector>
#include <memory>
#include <map>

#include "types/InputData.h"
#include "types/MainTypes.h"
#include "selection/ISelector.h"
#include "crossover/ICrossover.h"
#include "mutation/IMutator.h"
#include "Inverter.h"

namespace algorithm
{
class PopulationManager
{
public:
    PopulationManager(const types::InputData&);
    void findTheBestSolution();

private:
    int calculateBitsetLength() const;
    types::Population initilizePopulation() const;
    std::map<float, types::Point> calculateValues(const types::Population&) const;
    types::Population getElites(const std::map<float, types::Point>&) const;
    types::Population addElitesToPopulationIfNecessary(types::Population, const types::Population&) const;

    const types::InputData input;
    std::unique_ptr<selection::ISelector> selector;
    std::unique_ptr<crossover::ICrossover> crossover;
    std::unique_ptr<mutation::IMutator> mutator;
    std::unique_ptr<Inverter> inverter;
    const float xMin{ -10.0 };
    const float xMax{ 10.0 };
    const float yMin{ -10.0 };
    const float yMax{ 10.0 };
};
}
