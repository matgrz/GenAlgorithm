#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class OnePointCrossover : public CrossoverProvider
{
public:
    OnePointCrossover(int crossoverPercentage);

private:
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point&, const types::Point&) override;
};
}
}
