#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class ArithmeticCrossover : public CrossoverProvider
{
public:
    ArithmeticCrossover(int crossoverPercentage);

private:
    std::pair<types::Point, types::Point> crossoverTwoCreatures(const types::Point&, const types::Point&) override;
};
}
}
