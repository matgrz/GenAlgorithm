#include "HomogeneousCrossover.h"

namespace algorithm
{
namespace crossover
{
HomogeneousCrossover::HomogeneousCrossover(int crossoverPercentage)
    : ICrossover{crossoverPercentage}
{
}

types::Population HomogeneousCrossover::doCrossover(const types::Population& population)
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

int HomogeneousCrossover::getIndexOfRandomCreatureWorseThanCurrent(int popSize, int index)
{
    int randomIndexBase = std::rand() % (popSize - index);
    return (randomIndexBase == 0 ? 1 : randomIndexBase) + index;
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
