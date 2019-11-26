#include "ServicesFactory.h"

#include "selection/BestIndividualSelector.h"
#include "selection/RouletteSelector.h"
#include "selection/TournamentSelector.h"
#include "crossover/OnePointCrossover.h"
#include "crossover/TwoPointCrossover.h"
#include "crossover/HomogeneousCrossover.h"
#include "mutation/BoundaryMutator.h"
#include "mutation/PointMutator.h"

namespace algorithm
{
std::unique_ptr<selection::ISelector>
ServicesFactory::createSelector(types::SelectionMethods selectionMethod, int selectionParam)
{
    switch (selectionMethod)
    {
    case types::SelectionMethods::BEST_ONES:
        return std::make_unique<selection::BestIndividualSelector>(selectionParam);
    case types::SelectionMethods::ROULETTE_WHEEL:
        return std::make_unique<selection::RouletteSelector>(selectionParam);
    default:
        return std::make_unique<selection::TournamentSelector>(selectionParam);;
    }
}

std::unique_ptr<crossover::ICrossover> 
ServicesFactory::createCrossover(types::Crossovers crossoverType, int crossoverProbability)
{
    switch (crossoverType)
    {
    case types::Crossovers::ONE_POINT:
        return std::make_unique<crossover::OnePointCrossover>(crossoverProbability);
    case types::Crossovers::TWO_POINT:
        return std::make_unique<crossover::TwoPointCrossover>(crossoverProbability);
    default:
        return std::make_unique<crossover::HomogeneousCrossover>(crossoverProbability);
    }
}
std::unique_ptr<mutation::IMutator>
ServicesFactory::createMutator(types::Mutations mutationType, int mutationProbability)
{
    switch (mutationType)
    {
    case types::Mutations::BOUNDARY:
        return std::make_unique<mutation::BoundaryMutator>(mutationProbability);
    default:
        return std::make_unique<mutation::PointMutator>(mutationProbability, mutationType);
    }
}
}
