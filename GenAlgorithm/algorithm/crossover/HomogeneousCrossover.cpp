#include "HomogeneousCrossover.h"

namespace algorithm
{
namespace crossover
{
HomogeneousCrossover::HomogeneousCrossover(int crossoverPercentage)
    : CrossoverProvider{crossoverPercentage}
{
}

std::pair<types::Point, types::Point>
HomogeneousCrossover::crossoverTwoCreatures(const types::Point& firstParent, const types::Point& secondParent)
{
    auto [xFirst, xSecond] = crossoverBitsets(firstParent.first, secondParent.first);
    auto [yFirst, ySecond] = crossoverBitsets(firstParent.second, secondParent.second);

    return { types::Point{xFirst, yFirst}, types::Point{xSecond, ySecond} };
}

std::pair<types::Bitset, types::Bitset>
HomogeneousCrossover::crossoverBitsets(const types::Bitset& firstParent, const types::Bitset& secondParent)
{
    std::vector<bool> firstNewBitset{};
    std::vector<bool> secondNewBitset{};

    for (int index = 0; index < firstParent.getValue().size(); index++)
    {
        firstNewBitset.push_back(firstParent.getValue()[index]);
        secondNewBitset.push_back(secondParent.getValue()[index]);
        std::swap(firstNewBitset, secondNewBitset);
    }
    return { firstNewBitset , secondNewBitset};
}
}
}
