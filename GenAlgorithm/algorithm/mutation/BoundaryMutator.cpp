#include "BoundaryMutator.h"

namespace algorithm
{
namespace mutation
{
BoundaryMutator::BoundaryMutator(int mutationPercentage) : IMutator{ mutationPercentage }
{
}

void BoundaryMutator::mutatePopulation(types::Population& population)
{
    for (auto& creature : population)
    {
    if (shouldMutationOccur())
        mutateX(creature.first);
    if (shouldMutationOccur())
        mutateX(creature.second);
    }
}
void BoundaryMutator::mutateX(types::xValues& xValues)
{
    if (isLeftBoundryPicked())
        xValues.negateLeftBit();
    else
        xValues.negateRightBit();
}
void BoundaryMutator::mutateY(types::yValues& yValues)
{
    if (isLeftBoundryPicked())
        yValues.negateLeftBit();
    else
        yValues.negateRightBit();
}
bool BoundaryMutator::isLeftBoundryPicked()
{
    return std::rand() % 2;
}
}
}
