#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class TwoPointCrossover : public ICrossover
{
public:
    TwoPointCrossover(int);
    types::Population doCrossover(const types::Population&) override;

private:
    int getIndexOfRandomCreatureWorseThanCurrent(int, int);
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point& , const types::Point&);
    std::pair<int, int> getSplitIndexes(int);
    std::pair<types::Bitset, types::Bitset> crossoverBitsets(const types::Bitset&, const types::Bitset&);
};
}
}
