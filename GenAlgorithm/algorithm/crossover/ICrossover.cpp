#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
CrossoverProvider::CrossoverProvider(int crossoverPercentage) : crossoverPercentage{ crossoverPercentage }
{
}

bool CrossoverProvider::isCrossoverPicked()
{
    return std::rand() % 100 < crossoverPercentage;
}

int CrossoverProvider::getIndexOfRandomCreatureWorseThanCurrent(int popSize, int index)
{
    int randomIndexBase = std::rand() % (popSize - index);
    return (randomIndexBase == 0 ? 1 : randomIndexBase) + index;
}

types::Population CrossoverProvider::doCrossover(const types::Population& population)
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
}
}
