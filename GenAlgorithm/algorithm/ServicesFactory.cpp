#include "ServicesFactory.h"

#include "selection/BestIndividualSelector.h"
#include "selection/RouletteSelector.h"
#include "selection/TournamentSelector.h"
#include "crossover/OnePointCrossover.h"
#include "mutation/BoundaryMutator.h"

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
		return std::make_unique<selection::BestIndividualSelector>(selectionParam);;
	}
}

std::unique_ptr<crossover::ICrossover> 
ServicesFactory::createCrossover(types::Crossovers crossoverType, int crossoverProbability)
{
	// TODO switch
	return std::make_unique<crossover::OnePointCrossover>(crossoverProbability);
}
std::unique_ptr<mutation::IMutator>
ServicesFactory::createMutator(types::Mutations mutationType, int mutationProbability)
{
	// TODO switch
	return std::make_unique<mutation::BoundaryMutator>(mutationProbability);
}
}