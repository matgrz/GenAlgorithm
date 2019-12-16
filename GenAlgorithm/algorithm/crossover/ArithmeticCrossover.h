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
    Children crossoverTwoCreatures(const types::Point&, const types::Point&) override;
};
}
}
