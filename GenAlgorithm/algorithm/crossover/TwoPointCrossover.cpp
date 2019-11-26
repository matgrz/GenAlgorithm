#include "TwoPointCrossover.h"

namespace algorithm
{
namespace crossover
{
TwoPointCrossover::TwoPointCrossover(int crossoverPercentage) 
    : ICrossover{ crossoverPercentage }
{
}

types::Population TwoPointCrossover::doCrossover(const types::Population& population)
{
    types::Population newPopulation{};
    const int popSize = population.size();
    const int lastIndexWhichEnablesCrossoverWithWorseCreature = popSize - 1;

    for (int index = 0; index < lastIndexWhichEnablesCrossoverWithWorseCreature; index++)
    {
        if (isCrossoverPicked())
        {
            int partnerIndex = getIndexOfRandomCreatureWorseThanCurrent(popSize, index);
            auto [firstNewCreature, secondNewCreature] = 
                crossoverTwoCreatures(population[index], population[partnerIndex]);
            newPopulation.push_back(firstNewCreature);
            newPopulation.push_back(secondNewCreature);
        }
    }
    std::copy(population.begin(), population.end(), std::back_inserter(newPopulation));
    return newPopulation;
}

int TwoPointCrossover::getIndexOfRandomCreatureWorseThanCurrent(int popSize, int index)
{
    int randomIndexBase = std::rand() % (popSize - index);
    return (randomIndexBase == 0 ? 1 : randomIndexBase) + index;
}

std::pair<types::Point, types::Point>
TwoPointCrossover::crossoverTwoCreatures(const types::Point& firstParent, const types::Point& secondParent)
{
    auto [xFirst, xSecond] = crossoverBitsets(firstParent.first, secondParent.first);
    auto [yFirst, ySecond] = crossoverBitsets(firstParent.second, secondParent.second);

    return { types::Point{xFirst, yFirst}, types::Point{xSecond, ySecond} };
}

std::pair<int, int> TwoPointCrossover::getSplitIndexes(int bitsetSize)
{
    const int halfOfBitset{ bitsetSize / 2 };
    const int firstIndex{ 0 };
    const int lastIndex{ bitsetSize - 1 };

    int lowerIndex = std::rand() % halfOfBitset;
    int upperIndex = (std::rand() % halfOfBitset) + halfOfBitset - lowerIndex;
    return {lowerIndex == firstIndex ? 1 : lowerIndex, upperIndex == lastIndex ? upperIndex - 1 : upperIndex };
}

// first  [A][B][C]       new1 [A][E][C]
// second [D][E][F]  -->  new2 [D][B][F]
std::pair<types::Bitset, types::Bitset>
TwoPointCrossover::crossoverBitsets(const types::Bitset& first, const types::Bitset& second)
{
    const auto [lowerIndex, upperIdex] = getSplitIndexes(first.getValue().size());

    auto [a, bc] = first.splitAtIndex(lowerIndex);
    auto [d, ef] = second.splitAtIndex(lowerIndex);

    auto [b, c] = types::Bitset(bc).splitAtIndex(upperIdex);
    auto [e, f] = types::Bitset(ef).splitAtIndex(upperIdex);

    return { (types::Bitset(a) + types::Bitset(e)) + types::Bitset(c), 
             (types::Bitset(d) + types::Bitset(b)) + types::Bitset(f)};
}
}
}
