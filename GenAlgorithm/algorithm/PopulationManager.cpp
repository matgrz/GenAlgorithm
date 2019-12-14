#include "PopulationManager.h"

#include <cmath>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <random>
    
#include "selection/BestIndividualSelector.h"
#include "ServicesFactory.h"

namespace algorithm
{
PopulationManager::PopulationManager(const types::InputData& input)
    : input{ input }, 
      xMin{ input.centerX - input.radius },
      xMax{ input.centerX + input.radius },
      yMin{ input.centerY - input.radius },
      yMax{ input.centerY + input.radius }
{
    ServicesFactory factory{};
    selector = factory.createSelector(input.selectionMethod, input.selectionParameter);
    crossover = factory.createCrossover(input.crossoverMethod, input.crossoverProbability);
    mutator = factory.createMutator(input.mutationMethod, input.mutationProbability, xMin, xMax);
    std::srand(std::time(nullptr));
}

types::ResultsPerIteration PopulationManager::findTheBestSolution() const
{
    types::ResultsPerIteration allResults{};
    std::cout << "init pop\n";
    auto population = initilizePopulation();
    for (const auto& creature : population)
        std::cout << "x = " << creature.first << "\n";

    int iteration{ 0 };

    for (;;)
    {
        auto results = calculateValuesAndStoreIt(population, allResults, iteration);
        auto elites = getElites(results);

        auto selectedResults = selector->select(results);
        if (iteration++ == input.generationCount)
        {
            std::cout << "leaving loop\n";
            return allResults;
        }
        types::Population selectedPopulation = convertResultsToPopulation(selectedResults);
        
        std::cout << "\nafter selection\n";
        for (const auto& creature : selectedPopulation)
            std::cout << "x = " << creature.first << "\n";

        auto populationAfterCrossover = crossover->doCrossover(selectedPopulation);

        std::cout << "\nafter crossover\n";
        for (const auto& creature : populationAfterCrossover)
            std::cout << "x = " << creature.first << ", y = " << creature.second << "\n";

        mutator->mutatePopulation(populationAfterCrossover);  

        std::cout << "\nafter mutation\n";
        for (const auto& creature : populationAfterCrossover)
            std::cout << "x = " << creature.first << ", y = " << creature.second << "\n";

        population = addElitesToPopulationIfNecessary(populationAfterCrossover, elites);
    }
    return {};
}

int PopulationManager::calculateBitsetLength() const
{	
    return std::ceil(std::log2((xMax - xMin) * std::pow(10, input.accuracy)) + std::log2(1));
}

types::Population PopulationManager::initilizePopulation() const
{
    std::vector<types::Point> population{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(xMin, xMax);

    for (int creature = 0; creature < input.populationSize; creature++)
        population.push_back({ dist(gen), dist(gen) });
	
    return population;
}

std::map<float, types::Point> PopulationManager::calculateValuesAndStoreIt(
    const types::Population& population, types::ResultsPerIteration& allResults, const int iteration) const
{
    std::map<float, types::Point> values{};
    std::set<types::ResultValues> resultsForThisIteration{};

    const auto constFactor = (xMax - xMin) / (std::pow(2, calculateBitsetLength()) - 1);
    for (const auto& creature : population)
    {
        float value = calculateValue(creature.first, creature.second);
        values.insert({value, creature});
        resultsForThisIteration.insert(types::ResultValues{ creature.first, creature.second, value});
    }
    allResults[iteration] = resultsForThisIteration;
    return values;
}

types::Population PopulationManager::convertResultsToPopulation(const std::map<float, types::Point>& selectedResults) const
{
    types::Population selectedPopulation{};
    std::transform(selectedResults.begin(),
                   selectedResults.end(),
                   std::back_inserter(selectedPopulation),
                   [](auto& creature) {
                       return creature.second;
                   });
    return selectedPopulation;
}

float PopulationManager::calculateValue(float x, float y) const
{
    return std::pow(x, 2) + 2 * std::pow(y, 2) - 0.3 * std::cos(3 * 3.14 * x) * std::cos(4 * 3.14 * y) + 0.3;
}

//std::pair<float, float>
//PopulationManager::decodeBitsetsToFloats(const types::Point& creature, float constFactor) const
//{
//    auto x = xMin + creature.first.toDecimal() * constFactor;
//    auto y = xMin + creature.second.toDecimal() * constFactor;
//    return {x, y};
//}

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
