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

float CrossoverProvider::getValueFromZeroToOne() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distance(0.0, 1.0);

    return distance(gen);
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
            auto optionalChildren = crossoverTwoCreatures(population[index], population[partnerIndex]);
            
            if (optionalChildren)
            {
                newPopulation.push_back(optionalChildren->first);
                newPopulation.push_back(optionalChildren->second);
            }
        }
    }
    std::copy(population.begin(), population.end(), std::back_inserter(newPopulation));
    return newPopulation;
}
}
}
