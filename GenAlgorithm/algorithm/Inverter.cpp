#include "Inverter.h"

#include <random>
#include <set>

namespace algorithm
{
Inverter::Inverter(int inversionProbability) : inversionProbability{ inversionProbability }
{
}

void Inverter::performInversion(types::Population& population)
{
    for (auto& creature : population)
    {
        if (shouldPerformInversion())
            invertPartOfBitset(creature);
    }
}

bool Inverter::shouldPerformInversion() const
{
    return std::rand() % 100 < inversionProbability;
}
void Inverter::invertPartOfBitset(types::Point& creature)
{
    if (shouldInvertX())
        doInvertion(creature.first);
    else
        doInvertion(creature.second);
}

bool Inverter::shouldInvertX() const
{
    return std::rand() % 2;
}

int Inverter::getLowerIndex(const types::Bitset& bitset) const
{
    return std::rand() % (bitset.getValue().size() - 1);
}

int Inverter::getUpperIndex(const types::Bitset& bitset) const
{
    return (std::rand() % (bitset.getValue().size() - 1)) + 1;
}

void Inverter::doInvertion(types::Bitset& bitset)
{
    std::multiset<int> indexesToInvert{};
    indexesToInvert.insert(getLowerIndex(bitset));
    indexesToInvert.insert(getUpperIndex(bitset));

    for (int index = *indexesToInvert.begin(); index <= *std::prev(indexesToInvert.end()); index++)
        bitset.negateBit(index);
}
}