#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class TwoPointCrossover : public CrossoverProvider
{
public:
    TwoPointCrossover(int);

private:
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point& , const types::Point&) override;
    std::pair<int, int> getSplitIndexes(int);
    std::pair<types::Bitset, types::Bitset> crossoverBitsets(const types::Bitset&, const types::Bitset&);
};
}
}
