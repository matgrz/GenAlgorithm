#include "HeuristicCrossover.h"
#include <iostream>

namespace algorithm
{
namespace crossover
{
HeuristicCrossover::HeuristicCrossover(int crossoverPercentage)
    : CrossoverProvider{ crossoverPercentage }
{
}

std::pair<types::Point, types::Point> HeuristicCrossover::crossoverTwoCreatures(const types::Point& firstParent, const types::Point& secondParent)
{
    if (isCrossoverPossible(firstParent, secondParent))
        return doCrossover(firstParent, secondParent);
    else if (isCrossoverPossible(secondParent, firstParent))
        return doCrossover(secondParent, firstParent);

    return {};
}

bool HeuristicCrossover::isCrossoverPossible(const types::Point& lesserParent, const types::Point& greaterParent)
{
    return greaterParent.first > lesserParent.first && greaterParent.second > lesserParent.second;
}

std::pair<types::Point, types::Point> HeuristicCrossover::doCrossover(const types::Point& lesserParent, const types::Point& greaterParent)
{
    const auto k = getValueFromZeroToOne();
    types::Point firstChild;
    types::Point secondChild;

    std::cout << "Doing crossover\n";
    firstChild.first = k * (greaterParent.first - lesserParent.first) - lesserParent.first;
    firstChild.second = k * (greaterParent.second - lesserParent.second) - lesserParent.second;
    secondChild.first = firstChild.second;
    secondChild.second = firstChild.first;

    return {firstChild, secondChild};
}
}
}
