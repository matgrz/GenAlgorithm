#pragma once

#include "ICrossover.h"

namespace algorithm
{
namespace crossover
{
class OnePointCrossover : public ICrossover
{
public:
	OnePointCrossover(int crossoverPercentage);
	types::Population doCrossover(const types::Population& population) override;

private:
	int getIndexOfRandomCreatureWorseThanCurrent(int popSize, int index);
	types::Point crossoverTwoCreatures(const types::Point&, const types::Point&);
};
}
}