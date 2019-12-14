#include "ServicesFactory.h"

#include "selection/BestIndividualSelector.h"
#include "selection/RouletteSelector.h"
#include "selection/TournamentSelector.h"
#include "crossover/ArithmeticCrossover.h"
#include "mutation/UniformMutator.h"
#include "crossover/HeuristicCrossover.h"
#include "mutation/IndexChangeMutator.h"

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
    case types::Crossovers::ARITHMETIC:
        return std::make_unique<crossover::ArithmeticCrossover>(crossoverProbability);
    default:
        return std::make_unique<crossover::HeuristicCrossover>(crossoverProbability);
    }
}
std::unique_ptr<mutation::IMutator>
ServicesFactory::createMutator(types::Mutations mutationType, int mutationProbability, float xMin, float xMax)
{
    switch (mutationType)
    {
    case types::Mutations::UNIFORM:
        return std::make_unique<mutation::UniformMutator>(mutationProbability, xMin, xMax);
    default:
        return std::make_unique<mutation::IndexChangeMutator>(mutationProbability);
    }
}
}
