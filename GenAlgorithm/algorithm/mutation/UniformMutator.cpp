#include "UniformMutator.h"

namespace algorithm
{
namespace mutation
{
UniformMutator::UniformMutator(int mutationPercentag, float minVal, float maxVal) 
    : IMutator{ mutationPercentage }, minVal{minVal}, maxVal{maxVal}
{
}

void UniformMutator::mutatePopulation(types::Population& population)
{
    for (auto& creature : population)
        if (shouldMutationOccur())
            performMutation(creature);
}

void UniformMutator::performMutation(types::Point& creature)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distance(minVal, maxVal);

    if (shouldXIndexBeMutated())
        creature.first = distance(gen);
    else
        creature.second = distance(gen);
}

bool UniformMutator::shouldXIndexBeMutated()
{
    return std::rand() % 2;
}
}
}
