#include "OnePointCrossover.h"

#include <random>

namespace algorithm
{
namespace crossover
{
OnePointCrossover::OnePointCrossover(int crossoverPercentage)
    : CrossoverProvider{ crossoverPercentage }
{
}

std::pair<types::Point, types::Point>
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

    std::vector<bool> newSecondX(secondX.first);
    newSecondX.insert(newSecondX.end(), firstX.second.begin(), firstX.second.end());
    std::vector<bool> newSecondY(secondY.first);
    newSecondY.insert(newSecondY.end(), firstY.second.begin(), firstY.second.end());

    return { {types::xValues{newFirstX}, types::yValues{newFirstY}},
             {types::xValues{newSecondX}, types::yValues{newSecondY}} };
}
}
}
