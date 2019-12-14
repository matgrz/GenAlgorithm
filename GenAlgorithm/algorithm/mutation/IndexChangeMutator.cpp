#include "IndexChangeMutator.h"

namespace algorithm
{
namespace mutation
{
IndexChangeMutator::IndexChangeMutator(int mutationPercentage) : IMutator{ mutationPercentage }
{
}

void IndexChangeMutator::mutatePopulation(types::Population& population)
{
    for (auto& creature : population)
        if (shouldMutationOccur())
            mutateCreature(creature);
}

void IndexChangeMutator::mutateCreature(types::Point& creature)
{
    std::swap(creature.first, creature.second);
}
}
}
