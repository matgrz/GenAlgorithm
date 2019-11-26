#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class HomogeneousCrossover : public ICrossover
{
public:
    HomogeneousCrossover(int);
    types::Population doCrossover(const types::Population&) override;

private:
    int getIndexOfRandomCreatureWorseThanCurrent(int, int);
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point&, const types::Point&);
    std::pair<types::Bitset, types::Bitset> crossoverBitsets(const types::Bitset&, const types::Bitset&);
};
}
}
