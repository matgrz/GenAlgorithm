#include "OnePointCrossover.h"

#include <random>
#include <iostream>

namespace algorithm
{
namespace crossover
{
OnePointCrossover::OnePointCrossover(int crossoverPercentage)
    : ICrossover{ crossoverPercentage }
{
}

types::Population OnePointCrossover::doCrossover(const types::Population& population)
{
    types::Population newCreatures{};
    const int popSize = population.size();
    const int lastIndexWhichEnablesCrossoverWithWorseCreature = popSize - 1;

    for (int index = 0; index < lastIndexWhichEnablesCrossoverWithWorseCreature; index++)
    {
        if (isCrossoverPicked())
        {
            int partnerIndex = getIndexOfRandomCreatureWorseThanCurrent(popSize, index);
                newCreatures.push_back(crossoverTwoCreatures(population[index], population[partnerIndex]));
            newCreatures.push_back(crossoverTwoCreatures(population[partnerIndex], population[index]));
        }
    }
    std::copy(population.begin(), population.end(), std::back_inserter(newCreatures));
    return newCreatures;
}

int OnePointCrossover::getIndexOfRandomCreatureWorseThanCurrent(int popSize, int index)
{
    int randomIndexBase = std::rand() % (popSize - index);
    return (randomIndexBase == 0 ? 1 : randomIndexBase) + index;
}

types::Point
OnePointCrossover::crossoverTwoCreatures(const types::Point& firstParent, const types::Point& secondParent)
{
    auto firstX = firstParent.first.splitAtHalf();
    auto firstY = firstParent.second.splitAtHalf();
    auto secondX = secondParent.first.splitAtHalf();
    auto secondY = secondParent.second.splitAtHalf();

    std::vector<bool> newFirstX(firstX.first);
    newFirstX.insert(newFirstX.end(), secondX.second.begin(), secondX.second.end());
    std::vector<bool> newFirstY(firstY.first);
    newFirstY.insert(newFirstY.end(), secondY.second.begin(), secondY.second.end());

    return { types::xValues{newFirstX}, types::yValues{newFirstY}} ;
}
}
}
