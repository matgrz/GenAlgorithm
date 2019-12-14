#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class HeuristicCrossover : public CrossoverProvider
{
public:
    HeuristicCrossover(int crossoverPercentage);

private:
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point&, const types::Point&) override;
    bool isCrossoverPossible(const types::Point&, const types::Point&);
    std::pair<types::Point, types::Point> doCrossover(const types::Point&, const types::Point&);
};
}
}
