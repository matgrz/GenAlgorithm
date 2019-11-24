#include "PointMutator.h"

#include <random>
#include <iostream>

namespace algorithm
{
namespace mutation
{
PointMutator::PointMutator(int mutationPercentage, types::Mutations mutationType) 
    : IMutator(mutationPercentage),
      mutationType{mutationType}
{
}

void PointMutator::mutatePopulation(types::Population& population)
{
    const int bitsetLen = getBitsetLength(population);

    for (auto& creature : population)
        performMutation(creature, bitsetLen);
}

int PointMutator::getBitsetLength(const types::Population& population) const
{
    return population.front().first.getValue().size();
}

std::set<int> PointMutator::getIndexToMutate(int bitsetLength) const
{
    std::set<int> indexToMutate{ std::rand() % bitsetLength };

    if (mutationType == types::Mutations::TWO_POINT)
        indexToMutate.insert(std::rand() % bitsetLength);
    return indexToMutate;
}

void PointMutator::performMutation(types::Point& creature, int bitsetLen)
{
    if (shouldMutationOccur())
    {
        const auto indexToMutateX = getIndexToMutate(bitsetLen);
        for (const auto& index : indexToMutateX)
            creature.first.negateBit(index);
    }
    if (shouldMutationOccur())
    {
        const auto indexToMutateY = getIndexToMutate(bitsetLen);
        for (const auto& index : indexToMutateY)
            creature.second.negateBit(index);
    }
}
}
}