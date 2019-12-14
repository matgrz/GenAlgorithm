#pragma once

#include <memory>

#include "types/InputData.h"
#include "selection/ISelector.h"
#include "crossover/ICrossover.h"
#include "mutation/IMutator.h"

namespace algorithm
{
class ServicesFactory
{
public:
    std::unique_ptr<selection::ISelector> createSelector(types::SelectionMethods, int selectionParam);
    std::unique_ptr<crossover::ICrossover> createCrossover(types::Crossovers, int crossoverProbability);
    std::unique_ptr<mutation::IMutator> createMutator(types::Mutations, int mutationProbability, float xMin, float xMax);
};
}
