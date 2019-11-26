#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class HomogeneousCrossover : public CrossoverProvider
{
public:
    HomogeneousCrossover(int);

private:
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point&, const types::Point&) override;
    std::pair<types::Bitset, types::Bitset> crossoverBitsets(const types::Bitset&, const types::Bitset&);
};
}
}
