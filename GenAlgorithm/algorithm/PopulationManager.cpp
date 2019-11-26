#include "PopulationManager.h"

#include <cmath>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iterator>

#include "selection/BestIndividualSelector.h"
#include "ServicesFactory.h"

namespace algorithm
{
PopulationManager::PopulationManager(const types::InputData& input)
    : input{ input }
{
    ServicesFactory factory{};
    selector = factory.createSelector(input.selectionMethod, input.selectionParameter);
    crossover = factory.createCrossover(input.crossoverMethod, input.crossoverProbability);
    mutator = factory.createMutator(input.mutationMethod, input.mutationProbability);
    inverter = std::make_unique<Inverter>(input.inversionProbability);
}

void PopulationManager::findTheBestSolution()
{
    auto population = initilizePopulation();

    for (int iteration = 0; iteration < input.generationCount; iteration++)
    {
        std::cout << " ----- ITERATION " << iteration << " ----- \n\n";
        // 1. evaluation
        auto results = calculateValues(population);

        // store elites
        auto elites = getElites(results);

        // 2. selection
        auto selectedResults = selector->select(results);

        // 3. crossover
        types::Population selectedPopulation{};	// TODO extract a method
        std::transform(selectedResults.begin(),
            selectedResults.end(),
            std::back_inserter(selectedPopulation),
            [](auto& creature)
            {
                return creature.second;
            });

        // crossover call
        std::cout << "Before crossover\n";
        for (auto& cr : selectedPopulation)
            std::cout << cr.first.toString() << "\n";

        auto populationAfterCrossover = crossover->doCrossover(selectedPopulation);

        std::cout << "After crossover\n";
        for (auto& cr : populationAfterCrossover)
            std::cout << cr.first.toString() << "\n";

        // 4. mutation
        mutator->mutatePopulation(populationAfterCrossover);  

        // inversion
        inverter->performInversion(population);

        // add: elite strategy
        population = addElitesToPopulationIfNecessary(populationAfterCrossover, elites);
    }
}

int PopulationManager::calculateBitsetLength() const
{	
    return std::ceil(std::log2((xMax - xMin) * std::pow(10, input.accuracy)) + std::log2(1));
}

types::Population PopulationManager::initilizePopulation() const
{
    const int bitsetLength = calculateBitsetLength();
    std::vector<types::Point> population{};
    std::srand(std::time(nullptr));

    for (int creature = 0; creature < input.populationSize; creature++)
        population.push_back({ types::Bitset{bitsetLength}, types::Bitset{bitsetLength} });
	
    return population;
}

std::map<float, types::Point> 
    PopulationManager::calculateValues(const types::Population& population) const
{
    std::map<float, types::Point> values{};
    const auto constFactor = (xMax - xMin) / (std::pow(2, calculateBitsetLength()) - 1);

    for (const auto& creature : population)
    {
        std::cout << "DBG: x str = " << creature.first.toString() << ", y str = " << creature.second.toString() << "\n";
        auto x = xMin + creature.first.toDecimal() * constFactor;
        auto y = xMin + creature.second.toDecimal() * constFactor;
        float value = std::pow(x, 2) + 2 * std::pow(y, 2) - 0.3 * std::cos(3 * 3.14 * x) * std::cos(4 * 3.14 * y) - 0.3;
        std::cout << "DBG: x = " << x << ", y = " << y << ", value = " << value << "\n";
        values.insert({value, creature});
    }

    return values;
}

types::Population PopulationManager::getElites(const std::map<float, types::Point>& results) const
{
    types::Population elites{};
    std::map<float, types::Point>::const_iterator iter = results.begin();
    for (int index = 0; index < input.strategyPercent; index++)
    {
        elites.push_back(iter->second);
        ++iter;
    }
    return elites;
}
types::Population PopulationManager::addElitesToPopulationIfNecessary(
    types::Population population, const types::Population& elites) const
{
    for (const auto& elite : elites)
    {
        if (std::find(population.begin(), population.end(), elite) == population.end())
            population.push_back(elite);
    }

    return population;
}
}
